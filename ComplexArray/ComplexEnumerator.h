#pragma once

#include "ComplexView.h"

BEGIN_NAMESPACE;

generic <typename T> 
private ref class ViewEnumerator abstract : IEnumerator<T>
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


private ref class ComplexEnumerator : ViewEnumerator<ComplexView^>
{
public:
	virtual property ComplexView^ Current
	{
		ComplexView^ get()override;
	}
	ComplexEnumerator(double* base, int size);
	virtual ~ComplexEnumerator();
};

ref class ComplexEnum : ViewEnumerator<Complex^>, IEnumerable<Complex^>
{
public:
	virtual property Complex^ Current
	{
		Complex^ get()override;
	}
	ComplexEnum(double* base, int size);
	virtual ~ComplexEnum();
	virtual IEnumerator<Complex^>^ GetEnumerator(){return this;}

	virtual System::Collections::IEnumerator^ GetObjEnumerator()
		= System::Collections::IEnumerable::GetEnumerator
	{return this;}
};

//------------------------------------------------//

private ref class ComplexElementEnum : ViewEnumerator<double>, IEnumerable<double>
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


private ref class ArrayEnum : IEnumerator<double>, IEnumerable<double>
{
	double* base_;
	double* begin_;
	double* curr_;
	double* end_;
public:
	ArrayEnum(double* base, int size):base_(base), begin_(base-1), end_(base+size), curr_(base-1)
	{}
	virtual ~ArrayEnum(){}

	virtual property double Current{ double get(){return *curr_;}}
	virtual bool MoveNext(){ curr_ += 1; return curr_ < end_;}
	virtual void Reset(){curr_ = begin_;}
	virtual IEnumerator<double>^ GetEnumerator(){return this;}

	virtual System::Object^ ObjCurrent() = System::Collections::IEnumerator::Current::get
	{return Current;}
	virtual System::Collections::IEnumerator^ GetObjEnum() = System::Collections::IEnumerable::GetEnumerator
	{return this;}
};


END_NAMESPACE;
