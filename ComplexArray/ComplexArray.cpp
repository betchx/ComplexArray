// これは メイン DLL ファイルです。

#include "stdafx.h"

#include "ComplexArray.h"
#include <memory>
#include <cmath>

using namespace System::Collections::Generic;
using namespace System::Linq;

BEGIN_NAMESPACE;

ComplexArray::~ComplexArray()
{
	fftw_free(data_);
}

ComplexArray::!ComplexArray()
{
	fftw_free(data_);
}

ComplexArray::ComplexArray(int length, bool zero_clear)
{
	size_ = length * 2;
	allocate();
	if(zero_clear)
		memset(data_, 0, buf_size_); // init by zero if specified
}

ComplexArray::ComplexArray(int length)
{
	size_ = length * 2;
	allocate();
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
	memcpy_s(data_, buf_size_, other->data_, sizeof(double)*size_);
}

ComplexArray::ComplexArray(const ComplexArray% other)
{
	size_ = other.size_;
	allocate();
	memcpy_s(data_, buf_size_, other.data_, sizeof(double)*size_);
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

IEnumerable<double>^ ComplexArray::Real::get()
{
	return gcnew ComplexElementEnum(data_, size_);
}

IEnumerable<double>^ ComplexArray::Imag::get()
{
	return gcnew ComplexElementEnum(data_+1, size_);
}

array<double>^ ComplexArray::real()
{
  return Enumerable::ToArray(Real);
}
array<double>^ ComplexArray::imag()
{
  return Enumerable::ToArray(Imag);
}



Complex^ ComplexArray::default::get(int idx)
{
	return gcnew ComplexView(data_ + 2 * idx);
}

void ComplexArray::default::set(int idx, Complex^ c)
{
	data_[idx*2] = c->Real;
	data_[idx*2+1] = c->Imag;
}


System::Collections::IEnumerator^ ComplexArray::GetObjEnumerator()
{
	return GetEnumerator();
}


int ComplexArray::size::get()
{
	return size_;
}

int ComplexArray::Length::get()
{
	return size_ / 2;
}

double* ComplexArray::begin()
{
	return data_;
}

double* ComplexArray::end()
{
	if(!end_) end_ = data_ + size_;
	return end_;
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

// Operations
ComplexArray^ ComplexArray::fft()
{
	ComplexArray^ ans = gcnew ComplexArray(Length, false);

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
	ComplexArray^ ans = gcnew ComplexArray(Length, false);
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





IEnumerable<double>^ ComplexArray::Abs::get()
{
  return gcnew  ConvEnumerable(data_, size_, gcnew AbsConv());
}
IEnumerable<double>^ ComplexArray::Power::get()
{
  return gcnew  ConvEnumerable(data_, size_, gcnew PowerConv());
}
IEnumerable<double>^ ComplexArray::Ang::get()
{
  return gcnew  ConvEnumerable(data_, size_, gcnew AngConv());
}

array<double>^ ComplexArray::abs()
{
  int n = Length;
  array<double>^ res = gcnew array<double>(n);
  for(int i = 0; i < n; ++i)
  {
    double re = data_[2*i  ];
    double im = data_[2*i+1];
    res[i] = sqrt(re*re+im*im);
  }
  return res;
}

array<double>^ ComplexArray::power()
{
  int n = Length;
  array<double>^ res = gcnew array<double>(n);
  for(int i = 0; i < n; ++i)
  {
    double re = data_[2*i];
    double im = data_[2*i+1];
    res[i] = re*re+im*im;
  }
  return res;
}

array<double>^ ComplexArray::ang()
{
  int n = Length;
  array<double>^ res = gcnew array<double>(n);
  for(int i = 0; i < n; ++i)
  {
    double re = data_[2*i];
    double im = data_[2*i+1];
    res[i] = atan2(re,im);
  }
  return res;
}

END_NAMESPACE;
