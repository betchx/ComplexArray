// これは メイン DLL ファイルです。

#include "stdafx.h"

#include "ComplexArray.h"
#include <functional>
#include <cstdlib>
#include <memory>
#include <fftw3.h>

namespace ComplexArrayLib
{

ComplexArray::~ComplexArray()
{
  fftw_free(data_);
}

ComplexArray::!ComplexArray()
{
  fftw_free(data_);
}

ComplexArray::ComplexArray(int length, bool zero_clear /*= false*/)
{
  size_ = length * 2;
  allocate();
  if(zero_clear)
    memset(data_, 0, buf_size_); // init by zero
}


ComplexArray::ComplexArray(array<double>^ arr)
{
  size_ = arr->Length;
  allocate();
  for(int i = 0; i < size_; ++i)
  {
    data_[i] = arr[i];
  }
}

ComplexArray::ComplexArray(const ComplexArray^ other)
{
  size_ = other->size_;
  allocate();
  memcpy_s(data_, buf_size_, other->data_, 2*sizeof(double)*other->size_);
}

void ComplexArray::allocate()
{
  // convert to even number
  size_ /= 2;
  size_ *= 2;

  buf_size_ = sizeof(double)*size_;
  data_ = nullptr;
  double* ptr = (double*)fftw_malloc(buf_size_);
  if(ptr)
    data_ = ptr;
  else
    throw gcnew OutOfMemoryException();
}


ComplexArray^ ComplexArray::real(int size, IEnumerable<double> ^c)
{
  ComplexArray^ arr = gcnew ComplexArray(size, false);
  double* ptr = arr->data_;
  IEnumerator<double>^ e = c->GetEnumerator();
  while(e->MoveNext())
  {
    *(ptr++) = e->Current;
    *(ptr++) = 0.0;
  }
  return arr;
}

ComplexArray^ ComplexArray::real(IEnumerable<double> ^c)
{
  int size = 0;
  IEnumerator<double>^ e = c->GetEnumerator();
  while(e->MoveNext())
    ++size;
  return ComplexArray::real(size, c);
}

ComplexArray^ ComplexArray::real(array<double>^ arr)
{
  int len = arr->Length;
  ComplexArray^ ca = gcnew ComplexArray(len, false);
  double* ptr = ca->data_;
  for(int i = 0; i < len; ++i)
  {
    *(ptr++) = arr[i];
    *(ptr++) = 0.0;
  }
  return ca;
}

ComplexArray^ ComplexArray::imag(int size, IEnumerable<double> ^c)
{
  ComplexArray^ arr = gcnew ComplexArray(size, false);
  double* ptr = arr->data_;
  IEnumerator<double>^ e = c->GetEnumerator();
  while(e->MoveNext())
  {
    *(ptr++) = 0.0;
    *(ptr++) = e->Current;
  }
  return arr;
}

ComplexArray^ ComplexArray::imag(IEnumerable<double> ^c)
{
  int size = 0;
  IEnumerator<double>^ e = c->GetEnumerator();
  while(e->MoveNext())
    ++size;
  return ComplexArray::imag(size, c);
}

ComplexArray^ ComplexArray::imag(array<double>^ arr)
{
  int len = arr->Length;
  ComplexArray^ ca = gcnew ComplexArray(len, false);
  double* ptr = ca->data_;
  for(int i = 0; i < len; ++i)
  {
    *(ptr++) = 0.0;
    *(ptr++) = arr[i];
  }
  return ca;
}


IEnumerator<ComplexView^>^ ComplexArray::GetEnumerator()
{
  return gcnew ComplexEnumerator(data_, size_);
}


ComplexArray^ ComplexArray::operator+=(double d)
{
  double* ptr = begin();
  double* last = end();
  while(ptr!=last){
    *(ptr++) += d;
    ptr++;
  }
  return this;
}

ComplexArray^ ComplexArray::operator+(double d)
{
  ComplexArray^ res = gcnew ComplexArray(this->Length, false);
  double * pin = begin();
  double * pout = res->begin();
  double * last = end();
  while(pin != last){
    *(pout++) = *(pin++) + d;  // add only real
    *(pout++) = *(pin++);
  }
  return res;
}

ComplexArray^ ComplexArray::operator+=(Complex% c)
{
  return this+=%c;
}

ComplexArray^ ComplexArray::operator+=(Complex^ c)
{
  double* ptr = begin();
  double* last = end();
  double re = c->Real;
  double im = c->Imag;
  while(ptr!=last){
    *(ptr++) += re;
    *(ptr++) += im;
  }
  return this;
}

ComplexArray^ ComplexArray::operator+(Complex% c)
{
  return this + %c;
}

ComplexArray^ ComplexArray::operator+(Complex^ c)
{
  ComplexArray^ res = gcnew ComplexArray(this->Length, false);
  double * pin = begin();
  double * pout = res->begin();
  double * last = end();
  while(pin != last){
    *(pout++) = *(pin++) + c->Real;
    *(pout++) = *(pin++) + c->Imag;
  }
  return res;
}

ComplexArray^ ComplexArray::real_assign(IEnumerable<double>^ c)
{
  IEnumerator<double>^ e = c->GetEnumerator();
  double * ptr = begin();
  while( e->MoveNext() && ptr != end() )
  {
    *(ptr++) = e->Current;
    ++ptr;
  }
  return this;
}

ComplexArray^ ComplexArray::imag_assign(IEnumerable<double>^ c)
{
  IEnumerator<double>^ e = c->GetEnumerator();
  double * ptr = begin();
  while( e->MoveNext() && ptr != end() )
  {
    *(++ptr) = e->Current;
    ++ptr;
  }
  return this;
}

ComplexArray^ ComplexArray::operator+=(ComplexArray% ca)
{
  return this += %ca;
}

ComplexArray^ ComplexArray::operator+=(ComplexArray^ ca)
{
  if(size_ != ca->size_)
    throw gcnew ArgumentException("Different size");

  double* pout = begin();
  double* pin = ca->begin();
  double* end_ = end();
  while(pout != end_)
  {
    *(pout++) += *(pin++);
  }

  return this;
}

ComplexArray^ ComplexArray::operator+(ComplexArray% ca)
{
  return this + %ca;
}

ComplexArray^ ComplexArray::operator+(ComplexArray^ ca)
{
  if(size_ != ca->size_)
    throw gcnew ArgumentException("Different size");
  ComplexArray^ ans = gcnew ComplexArray(size_, false);

  double* pout = ans->begin();
  double* x = begin();
  double* y = ca->begin();
  while(x != end())
  {
    *(pout++) = *(x++) + *(y++);
  }

  return ans;
}

// Operations
ComplexArray^ ComplexArray::fft()
{
	ComplexArray^ ans = gcnew ComplexArray(size_, false);

	fftw_plan plan = fftw_plan_dft_1d(
		Length,                        // Data size
		(fftw_complex*)(data_),        // input
		(fftw_complex*)(ans->data_),   // output
		FFTW_FORWARD,                  // Direction
		FFTW_ESTIMATE);                // Option
	fftw_execute(plan);
	fftw_destroy_plan(plan);

	return ans;
}

ComplexArray^ ComplexArray::ifft()
{
	ComplexArray^ ans = gcnew ComplexArray(size_, false);
	fftw_plan plan = fftw_plan_dft_1d(
		Length,                        // Data size
		(fftw_complex*)(data_),        // input
		(fftw_complex*)(ans->data_),   // output
		FFTW_BACKWARD,                 // Direction
		FFTW_ESTIMATE);                // Option
	fftw_execute(plan);
	fftw_destroy_plan(plan);

	return ans;
}


}