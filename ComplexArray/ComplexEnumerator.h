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

ref class ComplexEnum : ComplexEnumerator, IEnumerable<ComplexView^>
{
public:
	ComplexEnum(double* base, int size);
	virtual ~ComplexEnum();
	virtual IEnumerator<ComplexView^>^ GetEnumerator(){return this;}

	virtual System::Collections::IEnumerator^ GetObjEnumerator()
		= System::Collections::IEnumerable::GetEnumerator
	{return this;}
};

//------------------------------------------------//

ref class ComplexElementEnum : ViewEnumerator<double>, IEnumerable<double>
{
public:
	virtual property double Current
	{
		double get() override;
	}

	ComplexElementEnum(double* base, int size);

	virtual ~ComplexElementEnum();

	virtual IEnumerator<double>^ GetEnumerator()
	  {return this;}

	virtual System::Collections::IEnumerator^ GetObjEnumerator()
		= System::Collections::IEnumerable::GetEnumerator
	{return this;}
};




END_NAMESPACE;