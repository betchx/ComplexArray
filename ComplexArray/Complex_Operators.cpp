#include "Stdafx.h"

#include "Complex.h"

BEGIN_NAMESPACE;


// add

Complex^ Complex::operator +(Complex^ c)
{
	return gcnew Complex(Real + c->Real, Imag + c->Imag);
}

Complex^ Complex::operator +(Complex% c)
{
	return gcnew Complex(Real + c.Real, Imag + c.Imag);
}

Complex^ Complex::operator +(double d)
{
	return gcnew Complex(Real + d, Imag);
}

Complex^ Complex::operator +(double d, Complex^ c)
{
	return gcnew Complex(c->Real + d, c->Imag);
}

Complex^ Complex::operator +(double d, Complex% c)
{
	return gcnew Complex(c.Real + d, c.Imag);
}



// sub

Complex^ Complex::operator-(double d)
{
	return gcnew Complex(Real-d, Imag);
}

Complex^ Complex::operator-(Complex^ c)
{
	return gcnew Complex(Real - c->Real, Imag - c->Imag);
}

Complex^ Complex::operator-(Complex% c)
{
	return gcnew Complex(Real - c.Real, Imag - c.Imag);
}

Complex^ Complex::operator-(double d, Complex^ c)
{
	return gcnew Complex(d - c->Real, - c->Imag);
}

Complex^ Complex::operator-(double d, Complex% c)
{
	return gcnew Complex(d - c.Real, - c.Imag);
}

// mul

Complex^ Complex::operator *(Complex^ c)
{
	return gcnew Complex(Real * c->Real - Imag * c->Imag, Real * c->Imag + Imag * c->Real);
}

Complex^ Complex::operator *(Complex% c)
{
	return gcnew Complex(Real * c.Real - Imag * c.Imag, Real * c.Imag + Imag * c.Real);
}

Complex^ Complex::operator *(double d)
{
	return gcnew Complex(Real * d, Imag * d);
}

Complex^ Complex::operator *(double d, Complex^ c)
{
	return gcnew Complex(c->Real * d, c->Imag * d);
}

Complex^ Complex::operator *(double d, Complex% c)
{
	return gcnew Complex(c.Real * d, c.Imag * d);
}



// div

Complex^ Complex::operator/(double d)
{
	return gcnew Complex(Real/d, Imag/d);
}

Complex^ Complex::operator/(Complex^ c)
{
	double a = c->Power;
    double r = (Real * c->Real + Imag * c->Imag) / a;
    double i = (Imag * c->Real - Real * c->Imag) / a;
	return gcnew Complex(r,i);
}

Complex^ Complex::operator/(Complex% c)
{
	double a = c.Power;
    double r = (Real * c.Real + Imag * c.Imag) / a;
    double i = (Imag * c.Real - Real * c.Imag) / a;
	return gcnew Complex(r,i);
}

Complex^ Complex::operator/(double d, Complex^ c)
{
	double a = c->Power;
	return gcnew Complex(d * c->Real / a, - d * c->Imag / a);
}

Complex^ Complex::operator/(double d, Complex% c)
{
	double a = c.Power;
	return gcnew Complex(d * c.Real / a, - d * c.Imag / a);
}


END_NAMESPACE;