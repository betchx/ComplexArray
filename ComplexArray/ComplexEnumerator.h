#pragma once

#include "ComplexView.h"

BEGIN_NAMESPACE;

generic <typename T> 
ref class ViewEnumerator abstract : IEnumerator<T>
{
protected:
	double* ptr;
	double* first;
	double* last;
public:

	virtual bool MoveNext();
	virtual void Reset();

	ViewEnumerator(double* base, int size);
	virtual ~ViewEnumerator();
	virtual System::Object^ ObjCurrent() = System::Collections::IEnumerator::Current::get
	{ 
		return Current;
	}
	virtual property T Current
	{
		T get() = 0;
	}
};


ref class ComplexEnumerator : ViewEnumerator<ComplexView^>
{
public:
	virtual property ComplexView^ Current
	{
		ComplexView^ get()override;
	}

	ComplexEnumerator(double* base, int size);

	virtual ~ComplexEnumerator();
};

//------------------------------------------------//

ref class ComplexElementEnumerator : ViewEnumerator<double>
{
public:
	virtual property double Current
	{
		double get() override;
	}

	ComplexElementEnumerator(double* base, int size);

	virtual ~ComplexElementEnumerator();
};

END_NAMESPACE;