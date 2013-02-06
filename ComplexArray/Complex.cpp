#include "Stdafx.h"

#include "Complex.h"

BEGIN_NAMESPACE;

Complex::Complex()
	:real_(0.0),imag_(0.0)
{}



Complex::Complex(double re, double im)
	:real_(re),imag_(im)
{}

Complex::Complex(double re)
	:real_(re),imag_(0.0)
{}

Complex::Complex(double* ptr)
	:real_(ptr[0]),imag_(ptr[1])
{}


Complex^ Complex::Conj::get()
{
	return gcnew Complex(Real, - Imag);
}

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

END_NAMESPACE;
