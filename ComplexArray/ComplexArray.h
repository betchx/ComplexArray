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

public protected:
	ComplexArray(double* data, int size):data_(data),size_(size){}
	ComplexArray(const ComplexArray% other);


public:
	virtual ~ComplexArray();
	!ComplexArray();
	ComplexArray(array<double>^ arr);
	ComplexArray(const ComplexArray^ other);
	ComplexArray(int length, bool zero_clear);
	ComplexArray(int length);

	static ComplexArray^ real(int size, IEnumerable<double> ^ e);
	static ComplexArray^ real(IEnumerable<double> ^ e);
	static ComplexArray^ real(array<double>^ arr);

	static ComplexArray^ imag(int size, IEnumerable<double> ^ e);
	static ComplexArray^ imag(IEnumerable<double> ^ e);
	static ComplexArray^ imag(array<double>^ arr);

	virtual IEnumerator<ComplexView^>^ GetEnumerator();
	virtual System::Collections::IEnumerator^ GetObjEnumerator()
		= System::Collections::IEnumerable::GetEnumerator;

	property IEnumerable<double>^ Real
	{
		IEnumerable<double>^ get();
	}
	property IEnumerable<double>^ Imag
	{
		IEnumerable<double>^ get();
	}

	property Complex^ default [int]
	{
		Complex^ get(int idx);
		void set(int idx, Complex^ value);
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

	static operator ComplexArray^ (ComplexArray %ca){return %ca;}

    // Definitions of operator +
    static ComplexArray^ operator +(ComplexArray^ lhs, double rhs);
    static ComplexArray^ operator +(double lhs, ComplexArray^ rhs);
    static ComplexArray^ operator +(ComplexArray^ lhs, Complex^ rhs);
    static ComplexArray^ operator +(Complex^ lhs, ComplexArray^ rhs);
    static ComplexArray^ operator +(ComplexArray^ lhs, ComplexArray^ rhs);

    // Definitions of operator *
    static ComplexArray^ operator *(ComplexArray^ lhs, double rhs);
    static ComplexArray^ operator *(double lhs, ComplexArray^ rhs);
    static ComplexArray^ operator *(ComplexArray^ lhs, Complex^ rhs);
    static ComplexArray^ operator *(Complex^ lhs, ComplexArray^ rhs);
    static ComplexArray^ operator *(ComplexArray^ lhs, ComplexArray^ rhs);

    // Definitions of operator -
    static ComplexArray^ operator -(ComplexArray^ lhs, double rhs);
    static ComplexArray^ operator -(double lhs, ComplexArray^ rhs);
    static ComplexArray^ operator -(ComplexArray^ lhs, Complex^ rhs);
    static ComplexArray^ operator -(Complex^ lhs, ComplexArray^ rhs);
    static ComplexArray^ operator -(ComplexArray^ lhs, ComplexArray^ rhs);

    // Definitions of operator /
    static ComplexArray^ operator /(ComplexArray^ lhs, double rhs);
    static ComplexArray^ operator /(double lhs, ComplexArray^ rhs);
    static ComplexArray^ operator /(ComplexArray^ lhs, Complex^ rhs);
    static ComplexArray^ operator /(Complex^ lhs, ComplexArray^ rhs);
    static ComplexArray^ operator /(ComplexArray^ lhs, ComplexArray^ rhs);

	// Operation

	ComplexArray^ fft();
	ComplexArray^ ifft();

    array<double>^ abs();
    array<double>^ ang();
    array<double>^ power();

};

END_NAMESPACE
