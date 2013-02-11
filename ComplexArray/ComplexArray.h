// ComplexArray.h

#pragma once


#include "Complex.h"
#include "ComplexView.h"
#include "ComplexEnumerator.h"

BEGIN_NAMESPACE;


public ref class ComplexArray : IEnumerable<Complex^>
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

	virtual IEnumerator<Complex^>^ GetEnumerator();
	virtual System::Collections::IEnumerator^ GetObjEnumerator()
		= System::Collections::IEnumerable::GetEnumerator;

	property IEnumerable<double>^ Real
	{
		IEnumerable<double>^ get();
		void set(IEnumerable<double>^ );
	}
	property IEnumerable<double>^ Imag
	{
		IEnumerable<double>^ get();
		void set(IEnumerable<double>^ );
	}

	array<double>^ real();
    array<double>^ imag();
	property Complex^ default [int]
	{
		Complex^ get(int idx);
		void set(int idx, Complex^ value);
	}

	property int Length { int get(); }
	property int size { int get(); }


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

    // Property will return IEnumerable
    property IEnumerable<double>^ Abs{ IEnumerable<double>^ get();}
    property IEnumerable<double>^ Ang{ IEnumerable<double>^ get();}
    property IEnumerable<double>^ Power{ IEnumerable<double>^ get();}


    // start with small letter mean function which return array<double>
    array<double>^ abs();
    array<double>^ ang();
    array<double>^ power();

};

END_NAMESPACE
