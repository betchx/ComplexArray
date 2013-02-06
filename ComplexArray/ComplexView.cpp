#pragma once

#include "Stdafx.h"
#include "ComplexView.h"

BEGIN_NAMESPACE;


ComplexView::ComplexView(double* origin)
	:Complex(origin),ptr_(origin)
{}


void ComplexView::Real::set(double value)
{
	real_ = value;
	ptr_[0] = value;
}


void ComplexView::Imag::set(double value)
{
	imag_ = value;
	ptr_[1] = value;
}


//ComplexView::operator Complex^(ComplexView^ v)
//{
//	return gcnew Complex(v->real_, v->imag_);
//}

END_NAMESPACE;
