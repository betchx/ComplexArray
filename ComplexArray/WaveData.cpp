#include "StdAfx.h"
#include "WaveData.h"

using namespace System::Runtime::InteropServices;

BEGIN_NAMESPACE;

WaveData::WaveData()
	:wave_(nullptr),sp_(nullptr),dirty_wave_(true),dirty_sp_(true),length_(0),wave_size_(0),sp_size_(0),w2s_(nullptr),s2w_(nullptr), wave_id_(0u), sp_id_(0u)
{}

WaveData::WaveData(int size)
	:wave_(nullptr), sp_(nullptr), wave_id_(0u), sp_id_(0u)
{
	allocate(size);
}

WaveData::WaveData(array<double>^ arr)
	:wave_(nullptr), sp_(nullptr), wave_id_(0u), sp_id_(0u)
{
	allocate(arr->Length);
	Marshal::Copy(arr, 0, (System::IntPtr)wave_, this->Length);
	wave_updated();
}

WaveData::WaveData(WaveData^ other)
	:wave_(nullptr),sp_(nullptr), wave_id_(0u), sp_id_(0u)
{
	allocate(other->Length);
	if( ! other->dirty_wave_ )
	{
		memcpy(wave_, other->wave_, length_ * sizeof(double) );
		dirty_wave_ = false;
	}
	if( ! other->dirty_sp_ )
	{
		std::copy(other->sp_->dbl_begin(), other->sp_->dbl_end(), sp_->dbl_begin());
		dirty_sp_ = false; // do not use sp_updated to avoid overwiting dirty_wave_;
	}
}

WaveData::WaveData(ComplexArray^ carr)
	:wave_(nullptr),sp_(nullptr), wave_id_(0u), sp_id_(0u)
{
	int len;
	if( carr->Length % 2 == 1){
		len = (carr->Length - 1) * 2;
	}else{
		len = carr->Length * 2;
	}
	allocate(len);
	double* ptr = sp_->dbl_begin();
	IEnumerator<ComplexArrayLib::Complex^>^ e = carr->GetEnumerator();
	double* end = sp_->dbl_end();
	while(e->MoveNext() && ptr != end)
	{
		*(ptr++)= e->Current->Real;
		*(ptr++)= e->Current->Imag;
	}
	sp_updated();
}

WaveData::WaveData(FFTWComplexArray* arr)
	:wave_(nullptr), sp_(nullptr), wave_id_(0u), sp_id_(0u)
{
	allocate(arr->size());
	memcpy(sp_->dbl_begin(), arr->dbl_begin(), length_*sizeof(fftw_complex));
	sp_updated();
}

WaveData::WaveData(std::complex<double>* begin, std::complex<double>* end)
	:wave_(nullptr), sp_(nullptr), wave_id_(0u), sp_id_(0u)
{
	allocate((int)(end  - begin));
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

int WaveData::Length::get(){return length_;}
int WaveData::WaveLength::get(){return length_;}
int WaveData::SpLength::get(){return sp_->size();}

void WaveData::clear_wave()
{
	memset(wave_, 0, wave_size_);
    wave_updated();
}

void WaveData::clear_sp()
{
	sp_->clear();
    sp_updated();
}

std::complex<double>& WaveData::sp::get(int idx){
  update_sp();
  return sp_->at(idx);
}
void WaveData::sp::set(int idx, std::complex<double>& value){
  sp_->set(idx, value);
  sp_updated();
}

bool WaveData::update()
{
	if(is_dirty()){
		update_wave();
		update_sp();
		return ! is_dirty();
	}else
		return false;
}



void WaveData::allocate(int length)
{
	if(! wave_){
		wave_ = (double*)fftw_malloc(sizeof(double) * length);
		dirty_wave_ = true;
	}
    int sp_length = length / 2 + 1;
	if(! sp_){
		sp_ = new FFTWComplexArray(sp_length);
		dirty_sp_ = true;
	}
	if(wave_ && sp_){
		length_ = length;
		sp_size_ = sp_length * sizeof(fftw_complex);
		wave_size_ = length * sizeof(double);
		w2s_ = fftw_plan_dft_r2c_1d(length, wave_, sp_->fftw(), FFTW_ESTIMATE);
		s2w_ = fftw_plan_dft_c2r_1d(length, sp_->fftw(), wave_, FFTW_ESTIMATE | FFTW_PRESERVE_INPUT  );
	}else{
		sp_size_ = wave_size_ = length_ = 0;
		w2s_ = nullptr;
		s2w_ = nullptr;
	}
}

void WaveData::update_wave()
{
	if(dirty_wave_ && ! dirty_sp_ && s2w_){
		fftw_execute(s2w_);
		std::transform(begin(), end(), begin(), std::bind2nd(std::divides<double>(), (double)length_));
		wave_id_update();
		dirty_wave_ = false;
	}
}

void WaveData::update_sp()
{
	if(dirty_sp_ && ! dirty_wave_ && w2s_)
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
	for(int i = 0; i < lhs->SpLength; ++i)
	{
		res->sp[i] = (lhs->sp[i]) * (rhs->sp[i]);
	}
	res->dirty_sp_ = false;

	return res;
}



// property Spectrum
Complex^ WaveData::Spectrum::get(int idx){
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
IEnumerable<Complex^>^ WaveData::Spectrum::get(){
  update_sp();
  return gcnew ComplexEnum(sp_->dbl_begin(), sp_->size() * 2);
}
void WaveData::Spectrum::set(IEnumerable<Complex^>^ arr)
{
	auto e = arr->GetEnumerator();
    auto it = sp_->begin();
	auto end_ = sp_->end();
	while( e->MoveNext() && it < end_)
	{
		it->real(e->Current->Real);
		it->imag(e->Current->Imag);
		++it;
	}
	sp_updated();
}


// property Wave
double WaveData::default::get(int idx){
  update_wave();
  return wave_[idx];
}
void WaveData::default::set(int idx, double value){
  wave_[idx] = value;
  wave_updated();
}
IEnumerable<double>^ WaveData::Wave::get(){
  update_wave();
  return gcnew ArrayEnum(wave_, length_);
}
void WaveData::Wave::set(IEnumerable<double>^ arr)
{
	auto e = arr->GetEnumerator();
	double* ptr = begin();
	double* end_ = end();
	while( e->MoveNext() && ptr < end_)
	{
		*(ptr++) = e->Current;
	}
	wave_updated();
}

// property Real
double WaveData::Real::get(int idx){
  update_sp();
  return sp_->at(idx).real();
}
void WaveData::Real::set(int idx, double value){
  sp_->at(idx).real(value);
  sp_updated();
}
IEnumerable<double>^ WaveData::Reals::get(){
  update_sp();
  return gcnew ComplexElementEnum(sp_->dbl_begin(), sp_->size());
}
void WaveData::Reals::set(IEnumerable<double>^ arr)
{
	auto e = arr->GetEnumerator();
	auto ptr = sp_->begin();
	auto end_ = sp_->end();
	while( e->MoveNext() && ptr < end_)
	{
		(ptr++)->real(e->Current);
	}
	sp_updated();
}

// property Imag
double WaveData::Imag::get(int idx){
  update_sp();
  return sp_->at(idx).imag();
}
void WaveData::Imag::set(int idx, double value){
  sp_->at(idx).imag(value);
  sp_updated();
}
IEnumerable<double>^ WaveData::Imags::get(){
  update_sp();
  return gcnew ComplexElementEnum(sp_->dbl_begin()+1, sp_->size());
}
void WaveData::Imags::set(IEnumerable<double>^ arr)
{
	auto e = arr->GetEnumerator();
	auto ptr = sp_->begin();
	auto end_ = sp_->end();
	while( e->MoveNext() && ptr < end_)
	{
		(ptr++)->imag(e->Current);
	}
	sp_updated();
}


IEnumerable<double>^ WaveData::Abs::get(){
  update_sp();
  return gcnew ConvEnum<AbsConv>(sp_->dbl_begin(), sp_->size());
}
IEnumerable<double>^ WaveData::Ang::get(){
  update_sp();
  return gcnew ConvEnum<AngConv>(sp_->dbl_begin(), sp_->size());
}
IEnumerable<double>^ WaveData::Power::get(){
  update_sp();
  return gcnew ConvEnum<PowerConv>(sp_->dbl_begin(), sp_->size());
}
IEnumerable<double>^ WaveData::dB::get(){
  update_sp();
  return gcnew ConvEnum<dBConv>(sp_->dbl_begin(), sp_->size());
}



//Test
void WaveData::Test::Allocation()
{
	int n = 10;
	WaveData^ wd = gcnew WaveData(n);
	Assert::AreEqual(n, wd->Length);
}

void WaveData::Test::CreateByArray()
{
	array<double>^ arr = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
	WaveData wd(arr);
	Assert::AreEqual(arr->Length, wd.Length);
	Assert::False(wd.dirty_wave_);
	Assert::True(wd.dirty_sp_);
	for(int i = 0; i < arr->Length; ++i)
	{
		Assert::AreEqual(arr[i], wd[i], 0.0001);
	}
}

void WaveData::Test::CreateByFullComplexArray()
{
	array<double>^ arr = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
	ComplexArray carr(arr);
	WaveData wd(carr);
	Assert::AreEqual(arr->Length, wd.Length);
	Assert::True(wd.dirty_wave_);
	Assert::False(wd.dirty_sp_);
	Assert::AreEqual(arr->Length/2+1, wd.SpLength);

	// check values
	Assert::AreEqual(1.0, wd.Real[0], 0.001);
	Assert::AreEqual(2.0, wd.Imag[0], 0.001);
	Assert::AreEqual(3.0, wd.Real[1], 0.001);
	Assert::AreEqual(4.0, wd.Imag[1], 0.001);
	Assert::AreEqual(5.0, wd.Real[2], 0.001);
	Assert::AreEqual(6.0, wd.Imag[2], 0.001);
}

void WaveData::Test::CreateByHalfComplexArray()
{
	array<double>^ arr = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
	ComplexArray carr(arr);
	Assert::AreEqual(arr->Length/2, carr.Length);
	WaveData wd(carr);
	Assert::AreEqual(arr->Length - 2, wd.Length);
	Assert::True(wd.dirty_wave_);
	Assert::False(wd.dirty_sp_);
	Assert::AreEqual(arr->Length/2, wd.SpLength);

	// check values
	Assert::AreEqual( 1.0, wd.Real[0], 0.001);
	Assert::AreEqual( 2.0, wd.Imag[0], 0.001);
	Assert::AreEqual( 3.0, wd.Real[1], 0.001);
	Assert::AreEqual( 4.0, wd.Imag[1], 0.001);
	Assert::AreEqual( 5.0, wd.Real[2], 0.001);
	Assert::AreEqual( 6.0, wd.Imag[2], 0.001);
	Assert::AreEqual( 7.0, wd.Real[3], 0.001);
	Assert::AreEqual( 8.0, wd.Imag[3], 0.001);
	Assert::AreEqual( 9.0, wd.Real[4], 0.001);
	Assert::AreEqual(10.0, wd.Imag[4], 0.001);
}

void WaveData::Test::PulseFFT()
{
	int n = 8;
	WaveData wd(n);
	wd.clear_wave();
	Assert::False(wd.dirty_wave_);
	Assert::True(wd.dirty_sp_);

	for(int i = 0; i < n; ++i)
	{
		Assert::AreEqual(0.0, wd[i], 0.0001);
	}

	wd[0] = 1.0;
	Assert::False(wd.dirty_wave_);
	Assert::True(wd.dirty_sp_);
	wd.Real[0];
	Assert::False(wd.dirty_wave_);
	Assert::False(wd.dirty_sp_);
	for(int i = 0; i < wd.SpLength; ++i)
	{
		Assert::AreEqual(1.0, wd.Real[i], 0.0001, "Real:" + (i).ToString());
		Assert::AreEqual(0.0, wd.Imag[i], 0.0001, "Imag:" + (i).ToString());
	}
}


void WaveData::Test::Wave()
{
	array<double>^ arr = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
	WaveData wd(arr);
	IEnumerator<double>^ e = wd.Wave->GetEnumerator();

	Assert::AreEqual(arr->Length, System::Linq::Enumerable::Count(wd.Wave));

	Assert::True(e->MoveNext());
	Assert::AreEqual(1.0, e->Current, 0.0001);
	Assert::True(e->MoveNext());
	Assert::AreEqual(2.0, e->Current, 0.0001);
	Assert::True(e->MoveNext());
	Assert::AreEqual(3.0, e->Current, 0.0001);
	Assert::True(e->MoveNext());
	Assert::AreEqual(4.0, e->Current, 0.0001);
	Assert::True(e->MoveNext());
	Assert::AreEqual(5.0, e->Current, 0.0001);
	Assert::True(e->MoveNext());
	Assert::AreEqual(6.0, e->Current, 0.0001);
	Assert::True(e->MoveNext());
	Assert::AreEqual(7.0, e->Current, 0.0001);
	Assert::True(e->MoveNext());
	Assert::AreEqual(8.0, e->Current, 0.0001);
	Assert::True(e->MoveNext());
	Assert::AreEqual(9.0, e->Current, 0.0001);
	Assert::True(e->MoveNext());
	Assert::AreEqual(10.0, e->Current, 0.0001);
    Assert::False(e->MoveNext());
}

void WaveData::Test::Spectrum()
{
	array<double>^ arr = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
	ComplexArray carr(arr);
	WaveData wd(carr);
	Assert::AreEqual(8, wd.Length);
	Assert::AreEqual(5, System::Linq::Enumerable::Count(wd.Spectrum));
	IEnumerator<Complex^>^ ce = carr.GetEnumerator();
	IEnumerator<Complex^>^ we = wd.Spectrum->GetEnumerator();
	Assert::True(ce->MoveNext());
	Assert::True(we->MoveNext());
	Assert::AreEqual(ce->Current->Real, we->Current->Real, 0.000001);
	Assert::AreEqual(arr[0], we->Current->Real, 0.000001);
	Assert::AreEqual(ce->Current->Imag, we->Current->Imag, 0.000001);
	Assert::AreEqual(arr[1], we->Current->Imag, 0.000001);
	Assert::True(ce->MoveNext());
	Assert::True(we->MoveNext());
	Assert::AreEqual(ce->Current->Real, we->Current->Real, 0.000001);
	Assert::AreEqual(arr[2], we->Current->Real, 0.000001);
	Assert::AreEqual(ce->Current->Imag, we->Current->Imag, 0.000001);
	Assert::AreEqual(arr[3], we->Current->Imag, 0.000001);
	Assert::True(ce->MoveNext());
	Assert::True(we->MoveNext());
	Assert::AreEqual(ce->Current->Real, we->Current->Real, 0.000001);
	Assert::AreEqual(arr[4], we->Current->Real, 0.000001);
	Assert::AreEqual(ce->Current->Imag, we->Current->Imag, 0.000001);
	Assert::AreEqual(arr[5], we->Current->Imag, 0.000001);
	Assert::True(ce->MoveNext());
	Assert::True(we->MoveNext());
	Assert::AreEqual(ce->Current->Real, we->Current->Real, 0.000001);
	Assert::AreEqual(arr[6], we->Current->Real, 0.000001);
	Assert::AreEqual(ce->Current->Imag, we->Current->Imag, 0.000001);
	Assert::AreEqual(arr[7], we->Current->Imag, 0.000001);
	Assert::True(ce->MoveNext());
	Assert::True(we->MoveNext());
	Assert::AreEqual(ce->Current->Real, we->Current->Real, 0.000001);
	Assert::AreEqual(arr[8], we->Current->Real, 0.000001);
	Assert::AreEqual(ce->Current->Imag, we->Current->Imag, 0.000001);
	Assert::AreEqual(arr[9], we->Current->Imag, 0.000001);
    Assert::False(ce->MoveNext());
	Assert::False(we->MoveNext());
}

void WaveData::Test::WaveAssign()
{
	array<double>^ arr = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
	WaveData^ wd = gcnew WaveData(arr->Length);
	wd->Wave = arr;
	for(int i = 0; i < 8; ++i)
	{
		Assert::AreEqual(arr[i], wd[i], 0.00001);
	}

	wd = gcnew WaveData(6);
	wd->Wave = arr;
	for(int i = 0; i < 6; ++i)
	{
		Assert::AreEqual(arr[i], wd[i], 0.0001);
	}
	wd = gcnew WaveData(10);
	wd->clear_wave();
	wd->Wave = arr;
	for(int i = 0; i < 8; ++i)
	{
		Assert::AreEqual(arr[i], wd[i], 0.00001);
	}
	Assert::AreEqual(0.0, wd[8], 0.00001);
	Assert::AreEqual(0.0, wd[9], 0.00001);

}

void WaveData::Test::Convolution()
{
	array<double>^ wave =   { 1.0,  0.7,  0.0, -0.7, -1.0, -0.7,  0.0,  0.7};
	array<double>^ tgt  =   { 0.0,  1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0};
	array<double>^ answer = { 0.7,  1.0,  0.7,  0.0, -0.7, -1.0, -0.7,  0.0};
    WaveData^ f = gcnew WaveData(wave);
	WaveData^ g = gcnew WaveData(tgt);
	WaveData^ res = f * g;
	for(int i =0; i < 8; ++i){
		Assert::AreEqual(answer[i], res[i], 0.00001, (i).ToString());
	}
}


void WaveData::Test::Abs()
{
    using namespace System::Linq;
    array<double>^ real = { -4.0, -3.0, -2.0, -1.0, 0.0, 1.0, 2.0, 3.0, 4.0};
    int n = real->Length;
    array<double>^ ans = gcnew array<double>(n);
    double rt2 = sqrt(2.0);
    for(int i = 0; i < n; ++i){
        ans[i] = rt2 * abs(real[i]);
    }

    WaveData^ wd = gcnew WaveData((n-(n%2))*2);
    wd->clear_sp();
    wd->Reals = real;

    array<double>^ res = Enumerable::ToArray(wd->Abs);

    Assert::AreEqual(n, res->Length);

    for(int i = 0; i < n; ++i)
    {
        Assert::AreEqual(fabs(real[i]), res[i], 0.00001, i.ToString());
    }

    wd->Imags = real;
    for(int i = 0; i < n; ++i)
    {
        Assert::AreEqual(real[i], wd->Real[i], 0.0001);
        Assert::AreEqual(real[i], wd->Imag[i], 0.0001);
    }
    res = Enumerable::ToArray(wd->Abs);
    for(int i = 0; i < n; ++i)
    {
        Assert::AreEqual(ans[i], res[i], 0.00001, i.ToString());
    }

}


void WaveData::Test::Power()
{
    using namespace System::Linq;
    array<double>^ real = { -4.0, -3.0, -2.0, -1.0, 0.0, 1.0, 2.0, 3.0, 4.0};
    int n = real->Length;
    array<double>^ ans = gcnew array<double>(n);
    for(int i = 0; i < n; ++i){
        ans[i] = 2 * real[i] * real[i];
    }

    WaveData^ wd = gcnew WaveData((n-(n%2))*2);
    wd->clear_sp();
    wd->Reals = real;

    array<double>^ res = Enumerable::ToArray(wd->Power);

    Assert::AreEqual(n, res->Length);

    for(int i = 0; i < n; ++i)
    {
        Assert::AreEqual(real[i]*real[i], res[i], 0.00001, i.ToString());
    }

    wd->Imags = real;
    for(int i = 0; i < n; ++i)
    {
        Assert::AreEqual(real[i], wd->Real[i], 0.0001);
        Assert::AreEqual(real[i], wd->Imag[i], 0.0001);
    }
    res = Enumerable::ToArray(wd->Power);
    for(int i = 0; i < n; ++i)
    {
        Assert::AreEqual(ans[i], res[i], 0.00001, i.ToString());
    }

}

void WaveData::Test::dB()
{
    using namespace System::Linq;
    array<double>^ real = { 0.001,  0.01,   0.1, 1.0, 10.0, 100.0, 1000.0};
    array<double>^  ans = {-120.0, -80.0, -40.0, 0.0, 40.0,  80.0,  120.0};

    int n = 7;
    int sz = 12;


    WaveData^ wd = gcnew WaveData(12);
    wd->clear_sp();
    wd->Reals = real;

    array<double>^ res = Enumerable::ToArray(wd->dB);

    Assert::AreEqual(n, res->Length);

    for(int i = 0; i < n; ++i)
    {
        Assert::AreEqual(real[i], wd->Real[i], 0.0001);
        Assert::AreEqual(    0.0, wd->Imag[i], 0.0001);
    }
    for(int i = 0; i < n; ++i)
    {
        Assert::AreEqual(ans[i], res[i], 0.00001, i.ToString());
    }

}

END_NAMESPACE;