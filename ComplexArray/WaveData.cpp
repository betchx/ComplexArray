#include "StdAfx.h"
#include "WaveData.h"

using namespace System::Runtime::InteropServices;

BEGIN_NAMESPACE;

WaveData::WaveData()
  :wave_(nullptr), sp_(nullptr), dirty_wave_(true), dirty_sp_(true), length_(0), wave_size_(0), sp_size_(0), w2s_(nullptr), s2w_(nullptr), wave_id_(0u), sp_id_(0u)
{}

WaveData::WaveData(int size)
  : wave_(nullptr), sp_(nullptr), wave_id_(0u), sp_id_(0u)
{
  allocate(size);
}

WaveData::WaveData(array<double>^ arr)
  : wave_(nullptr), sp_(nullptr), wave_id_(0u), sp_id_(0u)
{
  allocate(arr->Length);
  Marshal::Copy(arr, 0, (System::IntPtr)wave_, this->Length);
  wave_updated();
}

WaveData::WaveData(WaveData^ other)
  :wave_(nullptr), sp_(nullptr), wave_id_(0u), sp_id_(0u)
{
  allocate(other->Length);
  if (!other->dirty_wave_)
  {
    memcpy(wave_, other->wave_, length_ * sizeof(double));
    dirty_wave_ = false;
  }
  if (!other->dirty_sp_)
  {
    std::copy(other->sp_->dbl_begin(), other->sp_->dbl_end(), sp_->dbl_begin());
    dirty_sp_ = false; // do not use sp_updated to avoid overwiting dirty_wave_;
  }
}

WaveData::WaveData(ComplexArray^ carr)
  :wave_(nullptr), sp_(nullptr), wave_id_(0u), sp_id_(0u)
{
  int len;
  if (carr->Length % 2 == 1) {
    len = (carr->Length - 1) * 2;
  }
  else {
    len = carr->Length * 2;
  }
  allocate(len);
  double* ptr = sp_->dbl_begin();
  IEnumerator<ComplexArrayLib::Complex^>^ e = carr->GetEnumerator();
  double* end = sp_->dbl_end();
  while (e->MoveNext() && ptr != end)
  {
    *(ptr++) = e->Current->Real;
    *(ptr++) = e->Current->Imag;
  }
  sp_updated();
}

WaveData::WaveData(FFTWComplexArray* arr)
  :wave_(nullptr), sp_(nullptr), wave_id_(0u), sp_id_(0u)
{
  allocate(arr->size());
  memcpy(sp_->dbl_begin(), arr->dbl_begin(), length_ * sizeof(fftw_complex));
  sp_updated();
}

WaveData::WaveData(std::complex<double>* begin, std::complex<double>* end)
  :wave_(nullptr), sp_(nullptr), wave_id_(0u), sp_id_(0u)
{
  allocate((int)(end - begin));
  std::copy(begin, end, sp_->begin());
  sp_updated();
}

WaveData::WaveData(double* begin, double* end)
  :wave_(nullptr), sp_(nullptr), wave_id_(0u), sp_id_(0u)
{
  allocate((int)(end - begin));
  std::copy(begin, end, wave_);
  wave_updated();
}

WaveData::~WaveData(void)
{
  fftw_destroy_plan(w2s_);
  fftw_destroy_plan(s2w_);
  fftw_free(wave_);
  delete sp_;
}

int WaveData::Length::get() { return length_; }
int WaveData::WaveLength::get() { return length_; }
int WaveData::SpLength::get() { return sp_->size(); }

void WaveData::ClearWave()
{
  memset(wave_, 0, wave_size_);
  wave_updated();
}

void WaveData::ClearSpectrum()
{
  sp_->clear();
  sp_updated();
}

std::complex<double>& WaveData::sp::get(int idx) {
  update_sp();
  return sp_->at(idx);
}
void WaveData::sp::set(int idx, std::complex<double>& value) {
  sp_->set(idx, value);
  sp_updated();
}

bool WaveData::Update()
{
  if (IsDirty) {
    update_wave();
    update_sp();
    return !IsDirty;
  }
  else
    return false;
}

void WaveData::allocate(int length)
{
  if (!wave_) {
    wave_ = (double*)fftw_malloc(sizeof(double) * length);
    dirty_wave_ = true;
  }
  int sp_length = length / 2 + 1;
  if (!sp_) {
    sp_ = new FFTWComplexArray(sp_length);
    dirty_sp_ = true;
  }
  if (wave_ && sp_) {
    length_ = length;
    sp_size_ = sp_length * sizeof(fftw_complex);
    wave_size_ = length * sizeof(double);
    w2s_ = fftw_plan_dft_r2c_1d(length, wave_, sp_->fftw(), FFTW_ESTIMATE);
    s2w_ = fftw_plan_dft_c2r_1d(length, sp_->fftw(), wave_, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
  }
  else {
    sp_size_ = wave_size_ = length_ = 0;
    w2s_ = nullptr;
    s2w_ = nullptr;
  }
}

void WaveData::update_wave()
{
  if (dirty_wave_ && !dirty_sp_ && s2w_) {
    fftw_execute(s2w_);
    std::transform(begin(), end(), begin(), std::bind2nd(std::divides<double>(), (double)length_));
    wave_id_update();
    dirty_wave_ = false;
  }
}

void WaveData::update_sp()
{
  if (dirty_sp_ && !dirty_wave_ && w2s_)
  {
    fftw_execute(w2s_);
    sp_id_update();
    dirty_sp_ = false;
  }
}

WaveData^ WaveData::operator * (WaveData^ lhs, WaveData^ rhs)
{
  lhs->update_sp();
  rhs->update_sp();
  WaveData^ res = gcnew WaveData(lhs->Length);
  for (int i = 0; i < lhs->SpLength; ++i)
  {
    res->sp[i] = (lhs->sp[i]) * (rhs->sp[i]);
  }
  res->dirty_sp_ = false;

  return res;
}

// property Spectrum
Complex^ WaveData::Spectrum::get(int idx) {
  update_sp();
  return gcnew ComplexView(sp_->dbl_begin() + idx * 2);
}

void WaveData::Spectrum::set(int idx, Complex^ value)
{
  std::complex<double>& c = sp_->at(idx);
  c.real(value->Real);
  c.imag(value->Imag);
  sp_updated();
}

IEnumerable<Complex^>^ WaveData::Spectrum::get() {
  update_sp();
  return gcnew ComplexEnum(sp_->dbl_begin(), sp_->size() * 2);
}

void WaveData::Spectrum::set(IEnumerable<Complex^>^ arr)
{
  auto e = arr->GetEnumerator();
  auto it = sp_->begin();
  auto end_ = sp_->end();
  while (e->MoveNext() && it < end_)
  {
    it->real(e->Current->Real);
    it->imag(e->Current->Imag);
    ++it;
  }
  sp_updated();
}

// property Wave
double WaveData::default::get(int idx) {
  update_wave();
  return wave_[idx];
}

void WaveData::default::set(int idx, double value) {
  wave_[idx] = value;
  wave_updated();
}

IEnumerable<double>^ WaveData::Wave::get() {
  update_wave();
  return gcnew ArrayEnum(wave_, length_);
}

void WaveData::Wave::set(IEnumerable<double> ^ arr)
{
  auto e = arr->GetEnumerator();
  double* ptr = begin();
  double* end_ = end();
  while (e->MoveNext() && ptr < end_)
  {
    *(ptr++) = e->Current;
  }
  wave_updated();
}

// property Real
double WaveData::Real::get(int idx) {
  update_sp();
  return sp_->at(idx).real();
}

void WaveData::Real::set(int idx, double value) {
  sp_->at(idx).real(value);
  sp_updated();
}

IEnumerable<double>^ WaveData::Reals::get() {
  update_sp();
  return gcnew ComplexElementEnum(sp_->dbl_begin(), sp_->size());
}

void WaveData::Reals::set(IEnumerable<double> ^ arr)
{
  auto e = arr->GetEnumerator();
  auto ptr = sp_->begin();
  auto end_ = sp_->end();
  while (e->MoveNext() && ptr < end_)
  {
    (ptr++)->real(e->Current);
  }
  sp_updated();
}

// property Imag
double WaveData::Imag::get(int idx) {
  update_sp();
  return sp_->at(idx).imag();
}

void WaveData::Imag::set(int idx, double value) {
  sp_->at(idx).imag(value);
  sp_updated();
}

IEnumerable<double>^ WaveData::Imags::get() {
  update_sp();
  return gcnew ComplexElementEnum(sp_->dbl_begin() + 1, sp_->size());
}

void WaveData::Imags::set(IEnumerable<double> ^ arr)
{
  auto e = arr->GetEnumerator();
  auto ptr = sp_->begin();
  auto end_ = sp_->end();
  while (e->MoveNext() && ptr < end_)
  {
    (ptr++)->imag(e->Current);
  }
  sp_updated();
}

IEnumerable<double>^ WaveData::Abs::get() {
  update_sp();
  return gcnew ConvEnum<AbsConv>(sp_->dbl_begin(), sp_->size());
}

IEnumerable<double>^ WaveData::Ang::get() {
  update_sp();
  return gcnew ConvEnum<AngConv>(sp_->dbl_begin(), sp_->size());
}

IEnumerable<double>^ WaveData::Power::get() {
  update_sp();
  return gcnew ConvEnum<PowerConv>(sp_->dbl_begin(), sp_->size());
}

IEnumerable<double>^ WaveData::Decibel::get() {
  update_sp();
  return gcnew ConvEnum<dBConv>(sp_->dbl_begin(), sp_->size());
}


END_NAMESPACE;