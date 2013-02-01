#include "Stdafx.h"

#include "Complex.h"

BEGIN_NAMESPACE;

Complex::Complex(double re, double im)
	:real_(re),imag_(im)
{
}

Complex::Complex(IComplex^ c)
	:real_(c->Real),imag_(c->Imag)
{
}

IComplex^ Complex::Conj::get()
{ return gcnew Complex(real_, - imag_);}

double Complex::Real::get()
{
	return real_;
}

void Complex::Real::set(double value)
{
	real_ = value;
}

double Complex::Imag::get()
{
	return imag_;
}

void Complex::Imag::set(double value)
{
	imag_ = value;
}


Complex^ Complex::operator=(IComplex^ c)
{
	real_ = c->Real;
	imag_ = c->Imag;
	return this;
}

END_NAMESPACE;
