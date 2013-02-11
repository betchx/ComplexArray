#include "Stdafx.h"

#include "FFTWComplexArray.h"

using namespace System::Runtime::InteropServices;

BEGIN_NAMESPACE;

FFTWComplexArray::FFTWComplexArray(int length)
{
	data_.cptr = (fftw_complex*)fftw_malloc(length*sizeof(fftw_complex));
	if( data_.cptr)
		length_ = length;
}
FFTWComplexArray::FFTWComplexArray(array<double>^ arr)
{
	int length = (arr->Length / 2 );
	data_.ptr = (double*)fftw_malloc(length*sizeof(fftw_complex));
	if( data_.cptr){
		length_ = length;
		Marshal::Copy(arr, 0, (IntPtr)data_.ptr, length * 2);
	}
}

void FFTWComplexArray::clear()
{
	memset(data_.ptr, 0, length_ * sizeof(fftw_complex));
}

FFTWComplexArray::~FFTWComplexArray(){
	fftw_free(data_.cptr);
}

std::complex<double>& FFTWComplexArray::at(int idx){
	// index check
	if(idx >= length_) throw std::out_of_range(std::to_string(idx) + " exeed upper bound of " + std::to_string((length_-1)));
	if(idx < -length_) throw std::out_of_range(std::to_string(idx) + " exeed lower bound of " + std::to_string(-length_));
	// positive index
	if(idx >= 0) return data_.complex[idx];
	// negative index
	return data_.complex[length_ + idx];
}
const std::complex<double>& FFTWComplexArray::at(int idx)const{
	// remove const for DRY principal
	return const_cast<FFTWComplexArray*>(this)->at(idx);
}

void FFTWComplexArray::set(int idx, const double& re, const double& im){
	complex& c = at(idx);
	c.real(re); c.imag(im);
}


int FFTWComplexArray::normalize(int idx)const
{
	if(idx<0) idx += (idx/length_-1)*-length_;
	return idx % length_;
}


END_NAMESPACE;

///////////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace NUnit::Framework;
using namespace System::Runtime::InteropServices;

BEGIN_NAMESPACE;

// Separate test class because FFTWComplexArray is native class.
[TestFixture]
private ref class TestFFTWComplexArray
{
public:

	[Test] void ConstructWithSize()
	{
		int n = 10;
		FFTWComplexArray arr(n);
		Assert::AreEqual(n, arr.size());

		arr.clear();
		for(int i = 0; i < n; ++i)
		{
			Assert::AreEqual(0.0, arr[i].real(), 0.0001);
			Assert::AreEqual(0.0, arr[i].imag(), 0.0001);
		}
	}

	[Test] void ConstructWithArray()
	{
		double a=1.3, b=4.5, c=7.4, d=7.3, e=7.9, f=53.4, g = 9.8, h=10.3;
		array<double>^ src = {a, b, c, d, e, f, g, h};
		int n = src->Length / 2;
		FFTWComplexArray arr(src);

		Assert::False(arr.data_.ptr == NULL);

		for(int i = 0; i < src->Length; ++i)
		{
			double expect = src[i];
			double actual = *(arr.data_.ptr+i);
			Assert::AreEqual(expect, actual, 0.00001);
		}

		Assert::AreEqual(n, arr.size());

		for(int i = 0; i < n; ++i)
		{
			Assert::AreEqual(src[i*2], arr[i].real(), 0.0001);
			Assert::AreEqual(src[i*2+1], arr[i].imag(), 0.00001);
		}
	}

	[Test] void At()
	{
		int n = 10;
		FFTWComplexArray ca(n);
		double a = 10.0, b=11.0, c=12.0, d=13.0;
		double D = 0.000001;
		Assert::AreEqual(a, ca.at(0).real(a), D);
		Assert::AreEqual(b, ca[0].imag(b), D);
		Assert::AreEqual(c, ca.at(n-1).real(c), D);
		Assert::AreEqual(d, ca[n-1].imag(d), D);

		// negative index
		Assert::AreEqual(a, ca.at(-n).real(), D);
		Assert::AreEqual(b, ca.at(-n).imag(), D);
		Assert::AreEqual(c, ca.at(-1).real(), D);
		Assert::AreEqual(d, ca.at(-1).imag(), D);

		// out of bound check
		try{ ca.at(n); Assert::Fail("No exception thrown for n");}catch(std::exception& ){Assert::Pass();}
		try{ ca.at(-n-1); Assert::Fail("No exception thrown for -n -1");}catch(std::exception& ){Assert::Pass();}
	}

	[Test] void Set()
	{
		int n = 10;
		FFTWComplexArray ca(n);
		double a = 10.0, b=11.0, c=12.0, d=13.0;
		double D = 0.000001;

		ca.set(-n, a, b);
		Assert::AreEqual(a, ca[0].real(), D);
		Assert::AreEqual(b, ca[0].imag(), D);
		ca.set(n-1, c, d);
		Assert::AreEqual(c, ca.at(-1).real(), D);
		Assert::AreEqual(d, ca.at(-1).imag(), D);
	}
	[Test] void NegativeIndex()
	{
		int n = 10;
		FFTWComplexArray ca(n);
		double a = 10.0, b=11.0, c=12.0, d=13.0;
		double D = 0.000001;

		ca.set(0, a,b );
		ca.set(n-1, c, d);
		Assert::AreEqual(a, ca[-n].real(), D);
		Assert::AreEqual(b, ca[-3*n].imag(), D);
		Assert::AreEqual(c, ca[-1].real(), D);
		Assert::AreEqual(d, ca[-n-1].imag(), D);
	}
	[Test] void Normalize()
	{
		int n = 10;
		FFTWComplexArray ca(n);

		Assert::AreEqual(0, ca.normalize(0));
		Assert::AreEqual(0, ca.normalize(n));
		Assert::AreEqual(1, ca.normalize(1));
		Assert::AreEqual(n-1, ca.normalize(n-1));
		Assert::AreEqual(n-1, ca.normalize(-1));
	}
};

END_NAMESPACE;