#pragma once

#include "Complex.h"

BEGIN_NAMESPACE;

#ifndef IN_LIB
class ComplexView;
#else
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
#endif

END_NAMESPACE;
