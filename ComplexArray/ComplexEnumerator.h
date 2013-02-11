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

interface struct ICConverter
{
  double operator()(double re, double im);
};

ref class ConvEnumerator : IEnumerator<double>
{
  double *r_, *i_, *begin_, *end_;
  int size_;
  ICConverter^ conv_;
public:
  ConvEnumerator(double* ptr, int size, ICConverter^ conv)
    :r_(ptr-2), i_(ptr-1), begin_(ptr-2), end_(ptr+size),size_(size),conv_(conv)
  {}

  virtual ~ConvEnumerator(){}

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
         return conv_(*r_, *i_);
      }
	}  
};

ref class ConvEnumerable : IEnumerable<double>
{
  double* ptr_;
  int size_;
  ICConverter^ conv_;

public:
  ConvEnumerable(double* ptr, int size, ICConverter^ conv)
    :ptr_(ptr), size_(size),conv_(conv)
  {}

  virtual IEnumerator<double>^ GetEnumerator()
  {
    return gcnew ConvEnumerator(ptr_, size_, conv_);
  }

  virtual System::Collections::IEnumerator^ GetObjEnumerator()
    = System::Collections::IEnumerable::GetEnumerator
  {return GetEnumerator();} 

};

ref class AbsConv : ICConverter
{
public:
  virtual double operator()(double re, double im) 
  {
    return sqrt(re*re+im*im);
  }
};

ref class PowerConv : ICConverter
{
public:
  virtual double operator()(double re, double im) 
  {
    return re*re+im*im;
  }
};

ref class AngConv : ICConverter
{
public:
  virtual double operator()(double re, double im) 
  {
    return atan2(re,im);
  }
};


END_NAMESPACE;