#pragma once

#include "Stdafx.h"
#include "ComplexView.h"

BEGIN_NAMESPACE;


ComplexView::ComplexView(double* origin)
	:real_(*origin), imag_(*(origin+1))
{
}

IComplex^ ComplexView::Conj::get()
{
	return gcnew Complex(real_, imag_);
}


double ComplexView::Real::get()
{
	return real_;
}

void ComplexView::Real::set(double value)
{
	real_ = value;
}

double ComplexView::Imag::get()
{
	return imag_;
}

void ComplexView::Imag::set(double value)
{
	imag_ = value;
}


ComplexView^ ComplexView::operator=(IComplex^ c)
{
	real_ = c->Real;
	imag_ = c->Imag;
	return this;
}

END_NAMESPACE;
