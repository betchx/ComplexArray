#include "Stdafx.h"

#include "ComplexEnumerator.h"

BEGIN_NAMESPACE;

generic <typename T> 
bool ViewEnumerator<T>::MoveNext()
{
	return (++(++ptr)) < last;
}

generic <typename T> 
void ViewEnumerator<T>::Reset()
{
	ptr = first;
}

generic <typename T> 
ViewEnumerator<T>::ViewEnumerator(double* base, int size)
	:ptr(base-2),first(base-2),last(base+size)
{}

generic <typename T> 
ViewEnumerator<T>::~ViewEnumerator()
{}

ComplexEnum::ComplexEnum(double* base, int size)
	:ComplexEnumerator(base, size)
{}

ComplexEnum::~ComplexEnum()
{}

// 

ComplexView^ ComplexEnumerator::Current::get()
{
	if(ptr == first || ptr >= last)
		throw gcnew InvalidOperationException();
	return gcnew ComplexView(ptr);
}

ComplexEnumerator::ComplexEnumerator(double* base, int size)
	:ViewEnumerator(base, size)
{}

ComplexEnumerator::~ComplexEnumerator()
{}


double  ComplexElementEnum::Current::get()
{
	if(ptr == first || ptr >= last)
		throw gcnew InvalidOperationException();
	return *ptr;
}

ComplexElementEnum::ComplexElementEnum(double* base, int size)
	:ViewEnumerator(base, size)
{}

ComplexElementEnum::~ComplexElementEnum()
{}


END_NAMESPACE;
