
#pragma once

#include "Stdafx.h"

using namespace System;
using namespace System::Collections::Generic;

#define BEGIN_NAMESPACE namespace ComplexArrayLib{
#define END_NAMESPACE }

BEGIN_NAMESPACE;

public ref class Complex
{
protected:
	double real_;
	double imag_;

public:
	Complex();
	Complex(double re, double im);
	Complex(double re);
	Complex(double* ptr);

	property double Real
	{
		double get();
		virtual void set(double value);
	} 

	property double Imag
	{
		double get();
		virtual void set(double value);
	} 

	property double Power{ double get(){return Real*Real+Imag*Imag;}}
	property double Abs{ double get(){return Math::Sqrt(Power);} }
	property double Ang{ double get(){return Math::Atan2(Imag, Real);}}
	property Complex^ Conj{ Complex^ get(); }

      ////////////////////////////////////
	 // Opreators
	////////////////////////////////////

	// add
	Complex^ operator +(double d);
	Complex^ operator +(Complex^ c);
	Complex^ operator +(Complex% c);
	static Complex^ operator +(double d, Complex^ c);
	static Complex^ operator +(double d, Complex% c);

	// sub
	Complex^ operator -(double d);
	Complex^ operator -(Complex^ c);
	Complex^ operator -(Complex% c);
	static Complex^ operator -(double d, Complex^ c);
	static Complex^ operator -(double d, Complex% c);

	// mul
	Complex^ operator *(double d);
	Complex^ operator *(Complex^ c);
	Complex^ operator *(Complex% c);
	static Complex^ operator *(double d, Complex^ c);
	static Complex^ operator *(double d, Complex% c);

	// div
	Complex^ operator /(double d);
	Complex^ operator /(Complex^ c);
	Complex^ operator /(Complex% c);
	static Complex^ operator /(double d, Complex^ c);
	static Complex^ operator /(double d, Complex% c);

};



END_NAMESPACE;

