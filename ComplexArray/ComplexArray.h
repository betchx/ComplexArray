// ComplexArray.h

#pragma once

using namespace System;
using namespace System::Collections::Generic;


namespace ComplexArrayLib {

  public interface class IComplex
  {
    virtual property double Real { double get(); void set(double d);}
    virtual property double Imag { double get(); void set(double d);}
    virtual property double Power{ double get();}
    virtual property double Abs{ double get(); }
    virtual property double Ang{ double get();}
    virtual property IComplex^ Conj{ IComplex^ get(); } 
  };
  
  public ref class ComplexBase abstract : IComplex
  {
  public:
    virtual property double Power{ double get(){return Real*Real+Imag*Imag;}}
    virtual property double Abs{ double get(){return Math::Sqrt(Power);} }
    virtual property double Ang{ double get(){return Math::Atan2(Imag, Real);}}
    virtual property double Real{ double get() = 0; void set(double) = 0;}
    virtual property double Imag{ double get() = 0; void set(double) = 0;}
    virtual property IComplex^ Conj{ IComplex^ get()=0;} 
  };

  public ref class Complex :  ComplexBase
  {
    double real_;
    double imag_;

  public:
    Complex(double re, double im):real_(re),imag_(im){}
    Complex(IComplex^ c):real_(c->Real),imag_(c->Imag){}

    virtual property IComplex^ Conj{ IComplex^ get()override{ return gcnew Complex(real_, - imag_);}}

    virtual property double Real
    {
      double get()override{return real_;}
      void set(double value)override{real_ = value;}
    } 
    virtual property double Imag
    {
      double get()override{return imag_;}
      void set(double value)override{imag_ = value;}
    } 


    Complex^ operator=(IComplex^ c){
      real_ = c->Real;
      imag_ = c->Imag;
      return this;
    }

  };


  public ref class ComplexView : public ComplexBase
  {
    double& real_;
    double& imag_;

  public:

    // construct
    ComplexView(double* origin)
      :real_(*origin), imag_(*(origin+1))
    {}

    virtual property IComplex^ Conj{ IComplex^ get()override{return gcnew Complex(real_, imag_);}}

    virtual property double Real
    {
      double get()override{return real_;}
      void set(double value)override{real_ = value;}
    }

    virtual property double Imag
    {
      double get()override{return imag_;}
      void set(double value)override{imag_ = value;}
    }

    ComplexView^ operator=(IComplex^ c){
      real_ = c->Real;
      imag_ = c->Imag;
      return this;
    }

  };


  generic <typename T> 
  ref class ViewEnumerator : IEnumerator<T>
  {
  protected:
    double* ptr;
    double* first;
    double* last;
  public:

    virtual bool MoveNext()
    {
      return (++(++ptr)) != last;
    }
    virtual void Reset()
    {
      ptr = first;
    }

    ViewEnumerator(double* base, int size)
      :ptr(base-2),first(base-2),last(base+size)
    {}

    virtual ~ViewEnumerator()
    {
    }

    virtual System::Object^ ObjCurrent() = System::Collections::IEnumerator::Current::get
    { 
      return Current;
    }

    virtual property T Current
    {
      T get(){ throw gcnew NotImplementedException();}
    }

  };
  ref class ComplexEnumerator : ViewEnumerator<ComplexView^>
  {
  public:
    virtual property ComplexView^ Current
    {
      ComplexView^ get()override{
        if(ptr == first || ptr >= last)
          throw gcnew InvalidOperationException();
        return gcnew ComplexView(ptr);
      }
    }

    ComplexEnumerator(double* base, int size)
      :ViewEnumerator(base, size)
    {}

    virtual ~ComplexEnumerator()
    {
    }
  };
  ref class ComplexElementEnumerator : ViewEnumerator<double>
  {
  public:
    virtual property double Current
    {
      double get() override
      {
        if(ptr == first || ptr >= last)
          throw gcnew InvalidOperationException();
        return *ptr;
      }
    }

    ComplexElementEnumerator(double* base, int size)
      :ViewEnumerator(base, size)
    {}

    virtual ~ComplexElementEnumerator()
    {
    }
  };


  public ref class ComplexArray : IEnumerable<ComplexView^>
  {
    double* data_;  // begin();
    double* end_;
    int size_;
    size_t buf_size_;
    void allocate();

    double* begin(){return data_;}
    double* end(){
      if(!end_) end_ = data_ + buf_size_;
      return end_;
    }

  public:
    virtual ~ComplexArray();
    !ComplexArray();
    ComplexArray(cli::array<double>^ arr);
    ComplexArray(double* data, int size):data_(data),size_(size){}
    ComplexArray(const ComplexArray^ other);
    ComplexArray(int length, bool zero_clear);
    static ComplexArray^ real(int size, IEnumerable<double> ^ e);
    static ComplexArray^ real(IEnumerable<double> ^ e);
    static ComplexArray^ real(array<double>^ arr);

    static ComplexArray^ imag(int size, IEnumerable<double> ^ e);
    static ComplexArray^ imag(IEnumerable<double> ^ e);
    static ComplexArray^ imag(array<double>^ arr);

    virtual IEnumerator<ComplexView^>^ GetEnumerator()
    {
      return gcnew ComplexEnumerator(data_, size_);
    }

    virtual System::Collections::IEnumerator^ GetObjEnumerator() sealed
      = System::Collections::IEnumerable::GetEnumerator
    {
      return GetEnumerator();
    }

    property IEnumerator<double>^ Real
    {
      IEnumerator<double>^ get()
      {
        return gcnew ComplexElementEnumerator(data_, size_);
      }
    }
    property IEnumerator<double>^ Imag
    {
      IEnumerator<double>^ get()
      {
        return gcnew ComplexElementEnumerator(data_+1, size_);
      }
    }


    property ComplexView^ default [int]
    {
      ComplexView^ get(int idx){
        return gcnew ComplexView(data_+2*idx);
      }
    }
    property int Length
    {
      int get(){return size_/2;}
    }
    property int size
    {
      int get(){return size_;}
    }

    ComplexArray^ real_assign(IEnumerable<double>^ c);
    ComplexArray^ imag_assign(IEnumerable<double>^ c);



    ComplexArray^ operator+=(double d);
    ComplexArray^ operator+(double d);
    ComplexArray^ operator+=(Complex^ c);
    ComplexArray^ operator+(Complex^ c);
    ComplexArray^ operator+=(Complex% c);
    ComplexArray^ operator+(Complex% c);
    ComplexArray^ operator+=(ComplexArray^ ca);
    ComplexArray^ operator+(ComplexArray^ ca);
    ComplexArray^ operator+=(ComplexArray% ca);
    ComplexArray^ operator+(ComplexArray% ca);


  };
}
