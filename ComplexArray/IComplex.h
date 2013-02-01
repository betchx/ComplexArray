#pragma once

using namespace System;
using namespace System::Collections::Generic;

#define BEGIN_NAMESPACE namespace ComplexArrayLib{
#define END_NAMESPACE }


BEGIN_NAMESPACE;

  public interface class IComplex
  {
    virtual property double Real { double get(); void set(double d);}
    virtual property double Imag { double get(); void set(double d);}
    virtual property double Power{ double get();}
    virtual property double Abs{ double get(); }
    virtual property double Ang{ double get();}
    virtual property IComplex^ Conj{ IComplex^ get(); } 
  };

END_NAMESPACE


