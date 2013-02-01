#pragma once

#include "IComplex.h"

BEGIN_NAMESPACE;

public ref class ComplexBase abstract : IComplex
{
public:
	virtual property double Power{ double get(){return Real*Real+Imag*Imag;}}
	virtual property double Abs{ double get(){return Math::Sqrt(Power);} }
	virtual property double Ang{ double get(){return Math::Atan2(Imag, Real);}}
	virtual property double Real{ double get() = 0; void set(double) = 0;}
	virtual property double Imag{ double get() = 0; void set(double) = 0;}
	virtual property IComplex^ Conj{ IComplex^ get()=0;} 
};



END_NAMESPACE;
