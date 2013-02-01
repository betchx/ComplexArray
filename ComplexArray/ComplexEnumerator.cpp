#include "Stdafx.h"

#include "ComplexEnumerator.h"

BEGIN_NAMESPACE;

generic <typename T> 
bool ViewEnumerator<T>::MoveNext()
{
	return (++(++ptr)) != last;
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


double  ComplexElementEnumerator::Current::get()
{
	if(ptr == first || ptr >= last)
		throw gcnew InvalidOperationException();
	return *ptr;
}

ComplexElementEnumerator::ComplexElementEnumerator(double* base, int size)
	:ViewEnumerator(base, size)
{}

ComplexElementEnumerator::~ComplexElementEnumerator()
{
}


END_NAMESPACE;
