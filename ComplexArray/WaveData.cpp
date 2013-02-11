#include "StdAfx.h"
#include "WaveData.h"

using namespace System::Runtime::InteropServices;

BEGIN_NAMESPACE;

WaveData::WaveData()
	:wave_(nullptr),sp_(nullptr),dirty_wave_(true),dirty_sp_(true),length_(0),wave_size_(0),sp_size_(0),w2s_(nullptr),s2w_(nullptr)
{}

WaveData::WaveData(int size)
	:wave_(nullptr), sp_(nullptr)
{
	allocate(size);
}

WaveData::WaveData(array<double>^ arr)
	:wave_(nullptr), sp_(nullptr)
{
	allocate(arr->Length);
	Marshal::Copy(arr, 0, (System::IntPtr)wave_, this->Length);
	wave_updated();
}

WaveData::WaveData(WaveData^ other)
	:wave_(nullptr),sp_(nullptr)
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
	:wave_(nullptr),sp_(nullptr)
{
	int len;
	if( carr->Length % 2 == 1){
		len = (carr->Length - 1) * 2;
	}else{
		len = carr->Length * 2;
	}
	allocate(len);
	double* ptr = sp_->dbl_begin();
	IEnumerator<ComplexArrayLib::ComplexView^>^ e = carr->GetEnumerator();
	double* end = sp_->dbl_end();
	while(e->MoveNext() && ptr != end)
	{
		*(ptr++)= e->Current->Real;
		*(ptr++)= e->Current->Imag;
	}
	sp_updated();
}

WaveData::WaveData(FFTWComplexArray* arr)
	:wave_(nullptr), sp_(nullptr)
{
	allocate(arr->size());
	memcpy(sp_->dbl_begin(), arr->dbl_begin(), length_*sizeof(fftw_complex));
	sp_updated();
}

WaveData::WaveData(std::complex<double>* begin, std::complex<double>* end)
	:wave_(nullptr), sp_(nullptr)
{
	allocate((int)(end  - begin));
	std::copy(begin, end, sp_->begin());
	sp_updated();
}

WaveData::WaveData(double* begin, double* end)
	:wave_(nullptr), sp_(nullptr)
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
}

void WaveData::clear_sp()
{
	sp_->clear();
}

std::complex<double>& WaveData::sp::get(int idx){return sp_->at(idx);}
void WaveData::sp::set(int idx, std::complex<double>& value){sp_->set(idx, value);}


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
		dirty_wave_ = false;
	}
}

void WaveData::update_sp()
{
	if(dirty_sp_ && ! dirty_wave_ && w2s_)
	{
		fftw_execute(w2s_);
		dirty_sp_ = false;
	}
}

WaveData^ WaveData::operator * (WaveData^ lhs, WaveData^ rhs)
{
	lhs->update_sp();
	rhs->update_sp();
	WaveData^ res = gcnew WaveData(lhs->Length);
	for(int i = 0; i < lhs->Length; ++i)
	{
		res->sp[i] = (lhs->sp[i]) * (rhs->sp[i]);
	}
	res->dirty_sp_ = false;

	return res;
}


ref class ArrayEnum : IEnumerator<double>, IEnumerable<double>
{
	double* base_;
	double* begin_;
	double* curr_;
	double* end_;
public:
	ArrayEnum(double* base, int size):base_(base), begin_(base-1), end_(base+size), curr_(base-1)
	{}
	virtual ~ArrayEnum(){}

	virtual property double Current{ double get(){return *curr_;}}
	virtual bool MoveNext(){ curr_ += 1; return curr_ < end_;}
	virtual void Reset(){curr_ = begin_;}
	virtual IEnumerator<double>^ GetEnumerator(){return this;}

	virtual System::Object^ ObjCurrent() = System::Collections::IEnumerator::Current::get
	{return Current;}
	virtual System::Collections::IEnumerator^ GetObjEnum() = System::Collections::IEnumerable::GetEnumerator
	{return this;}
};

// property Spectrum
IEnumerable<ComplexView^>^ WaveData::Spectrum::get(){return gcnew ComplexEnum(sp_->dbl_begin(), sp_->size() * 2); }


// property Wave
double WaveData::Wave::get(int idx){update_wave();return wave_[idx];}
void WaveData::Wave::set(int idx, double value){ wave_[idx] = value; wave_updated();}
IEnumerable<double>^ WaveData::Wave::get(){return gcnew ArrayEnum(wave_, length_);}

// property Real
double WaveData::Real::get(int idx){update_sp(); return sp_->at(idx).real();}
void WaveData::Real::set(int idx, double value){ sp_->at(idx).real(value); sp_updated();}
IEnumerable<double>^ WaveData::Real::get(){return gcnew ComplexElementEnum(sp_->dbl_begin(), sp_->size());}

// property Imag
double WaveData::Imag::get(int idx){update_sp(); return sp_->at(idx).imag();}
void WaveData::Imag::set(int idx, double value){ sp_->at(idx).imag(value); sp_updated();}
IEnumerable<double>^ WaveData::Imag::get(){return gcnew ComplexElementEnum(sp_->dbl_begin()+1, sp_->size());}



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
		Assert::AreEqual(arr[i], wd.Wave[i], 0.0001);
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
	Assert::True(wd.dirty_wave_);
	Assert::True(wd.dirty_sp_);

	for(int i = 0; i < n; ++i)
	{
		Assert::AreEqual(0.0, wd.Wave[i], 0.0001);
	}

	wd.Wave[0] = 1.0;
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
	IEnumerator<ComplexView^>^ ce = carr.GetEnumerator();
	IEnumerator<ComplexView^>^ we = wd.Spectrum->GetEnumerator();
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

END_NAMESPACE;