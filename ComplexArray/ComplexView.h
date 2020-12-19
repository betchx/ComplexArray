#pragma once

#include "Complex.h"

BEGIN_NAMESPACE;

public ref class ComplexView : Complex
{
	double* ptr_;

public:

	// construct
	ComplexView(double* origin);

	property double Real
	{
		virtual void set(double value) override;
	}

	property double Imag
	{
		virtual void set(double value) override;
	}

//	static operator Complex^(ComplexView^ v);
};

END_NAMESPACE;
