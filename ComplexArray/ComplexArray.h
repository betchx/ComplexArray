// ComplexArray.h

#pragma once


#include "Complex.h"
#include "ComplexView.h"
#include "ComplexEnumerator.h"

BEGIN_NAMESPACE;


public ref class ComplexArray : IEnumerable<ComplexView^>
{
	double* data_;  // begin();
	double* end_;
	int size_;
	size_t buf_size_;
	void allocate();

	double* begin();
	double* end();

public:
	virtual ~ComplexArray();
	!ComplexArray();
	ComplexArray(array<double>^ arr);
	ComplexArray(double* data, int size):data_(data),size_(size){}
	ComplexArray(const ComplexArray^ other);
	ComplexArray(int length, bool zero_clear);
	static ComplexArray^ real(int size, IEnumerable<double> ^ e);
	static ComplexArray^ real(IEnumerable<double> ^ e);
	static ComplexArray^ real(array<double>^ arr);

	static ComplexArray^ imag(int size, IEnumerable<double> ^ e);
	static ComplexArray^ imag(IEnumerable<double> ^ e);
	static ComplexArray^ imag(array<double>^ arr);

	virtual IEnumerator<ComplexView^>^ GetEnumerator();
	virtual System::Collections::IEnumerator^ GetObjEnumerator()
		= System::Collections::IEnumerable::GetEnumerator
	{
		return GetEnumerator();
	}

	property IEnumerator<double>^ Real
	{
		IEnumerator<double>^ get();
	}
	property IEnumerator<double>^ Imag
	{
		IEnumerator<double>^ get();
	}

	property ComplexView^ default [int]
	{
		ComplexView^ get(int idx);
	}


	property int Length
	{
		int get();
	}
	property int size
	{
		int get();
	}

	ComplexArray^ real_assign(IEnumerable<double>^ c);
	ComplexArray^ imag_assign(IEnumerable<double>^ c);

	ComplexArray^ operator+=(double d);
	ComplexArray^ operator+(double d);
	ComplexArray^ operator+=(Complex^ c);
	ComplexArray^ operator+(Complex^ c);
	ComplexArray^ operator+=(Complex% c);
	ComplexArray^ operator+(Complex% c);
	ComplexArray^ operator+=(ComplexArray^ ca);
	ComplexArray^ operator+(ComplexArray^ ca);
	ComplexArray^ operator+=(ComplexArray% ca);
	ComplexArray^ operator+(ComplexArray% ca);


	// Operation

	ComplexArray^ fft();
	ComplexArray^ ifft();

};

END_NAMESPACE
