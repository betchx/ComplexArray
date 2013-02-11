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


//---------------------------------------------------//


template<typename Conv>
private ref class ConvEnum : IEnumerator<double>, IEnumerable<double>
{
	double *r_, *i_, *begin_, *end_;
	int size_;
public:
	ConvEnum(double* ptr, int size)
		:r_(ptr-2), i_(ptr-1), begin_(ptr-2), end_(ptr+size),size_(size)
	{}

	virtual ~ConvEnum(){}

	virtual bool MoveNext()
	{
		r_+=2;
		i_+=2;
		return r_ < end_;
	}
	virtual void Reset()
	{
		r_ = begin_;
		i_ = begin_+1;
	}
	virtual System::Object^ ObjCurrent() = System::Collections::IEnumerator::Current::get
	{ 
		return Current;
	}
	virtual property double Current
	{
		double get()
		{
			return Conv::convert(*r_, *i_);
		}
	}  

	virtual IEnumerator<double>^ GetEnumerator()
	{
		return this;
	}

	virtual System::Collections::IEnumerator^ GetObjEnumerator()
		= System::Collections::IEnumerable::GetEnumerator
	{return GetEnumerator();} 

};

private struct AbsConv
{
	static double convert(const double& re, const double& im) 
	{
		return sqrt(re*re+im*im);
	}
};

private struct PowerConv
{
	static double convert(const double& re, const double& im) 
	{
		return re*re+im*im;
	}
};

private struct AngConv
{
	static double convert(const double& re, const double& im) 
	{
		return atan2(re,im);
	}
};




END_NAMESPACE;
