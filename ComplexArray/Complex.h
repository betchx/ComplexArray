
#pragma once

#include "Stdafx.h"
#include "ComplexBase.h"


BEGIN_NAMESPACE;

public ref class Complex :  ComplexBase
{
	double real_;
	double imag_;

public:
	Complex(double re, double im);
	Complex(IComplex^ c);

	virtual property IComplex^ Conj{
		IComplex^ get()override;
	}

	virtual property double Real
	{
		double get()override;
		void set(double value)override;
	} 

	virtual property double Imag
	{
		double get()override;
		void set(double value)override;
	} 

	Complex^ operator=(IComplex^ c);

};



END_NAMESPACE;

