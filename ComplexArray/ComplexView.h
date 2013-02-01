#pragma once

#include "Complex.h"

BEGIN_NAMESPACE;
public ref class ComplexView : public ComplexBase
{
	double& real_;
	double& imag_;

public:

	// construct
	ComplexView(double* origin);

	virtual property IComplex^ Conj
	{
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

	ComplexView^ operator=(IComplex^ c);

};
END_NAMESPACE;
