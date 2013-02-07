#include "Stdafx.h"

#include "Complex.h"

BEGIN_NAMESPACE;


// add

Complex^ Complex::operator +(Complex^ s, Complex^ c)
{
	return gcnew Complex(s->Real + c->Real, s->Imag + c->Imag);
}


Complex^ Complex::operator +(Complex^ c, double d)
{
	return gcnew Complex(c->Real + d, c->Imag);
}

Complex^ Complex::operator +(double d, Complex^ c)
{
	return gcnew Complex(c->Real + d, c->Imag);
}


// sub

Complex^ Complex::operator-(Complex^ s, double d)
{
	return gcnew Complex(s->Real - d, s->Imag);
}

Complex^ Complex::operator-(Complex^ s, Complex^ c)
{
	return gcnew Complex(s->Real - c->Real, s->Imag - c->Imag);
}

Complex^ Complex::operator-(double d, Complex^ c)
{
	return gcnew Complex(d - c->Real, - c->Imag);
}

// mul

Complex^ Complex::operator *(Complex^ s, Complex^ c)
{
	return gcnew Complex(s->Real * c->Real - s->Imag * c->Imag, s->Real * c->Imag + s->Imag * c->Real);
}

Complex^ operator *(Complex s, Complex^ c)
{
	return gcnew Complex(s.Real * c->Real - s.Imag * c->Imag, s.Real * c->Imag + s.Imag * c->Real);
}

Complex^ Complex::operator *(Complex^ s, double d)
{
	return gcnew Complex(s->Real * d, s->Imag * d);
}

Complex^ Complex::operator *(double d, Complex^ c)
{
	return gcnew Complex(c->Real * d, c->Imag * d);
}




// div

Complex^ Complex::operator/(Complex^ s, double d)
{
	return gcnew Complex(s->Real / d, s->Imag / d);
}

Complex^ Complex::operator/(Complex^ s, Complex^ c)
{
	double a = c->Power;
    double r = (s->Real * c->Real + s->Imag * c->Imag) / a;
    double i = (s->Imag * c->Real - s->Real * c->Imag) / a;
	return gcnew Complex(r,i);
}


Complex^ Complex::operator/(double d, Complex^ c)
{
	double a = c->Power;
	return gcnew Complex(d * c->Real / a, - d * c->Imag / a);
}

END_NAMESPACE;