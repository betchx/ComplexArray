#include "Stdafx.h"
#include "ComplexArray.h"


BEGIN_NAMESPACE;

ComplexArray^ ComplexArray::operator+=(double d)
{
	double* ptr = begin();
	double* last = end();
	while(ptr!=last){
		*(ptr++) += d;
		ptr++;
	}
	return this;
}


ComplexArray^ ComplexArray::operator+=(Complex% c)
{
	return this+=%c;
}

ComplexArray^ ComplexArray::operator+=(Complex^ c)
{
	double* ptr = begin();
	double* last = end();
	double re = c->Real;
	double im = c->Imag;
	while(ptr!=last){
		*(ptr++) += re;
		*(ptr++) += im;
	}
	return this;
}

ComplexArray^ ComplexArray::operator+=(ComplexArray% ca)
{
	return this += %ca;
}

ComplexArray^ ComplexArray::operator+=(ComplexArray^ ca)
{
	if(size_ != ca->size_)
		throw gcnew ArgumentException("Different size");

	double* pout = begin();
	double* pin = ca->begin();
	double* end_ = end();
	while(pout != end_)
	{
		*(pout++) += *(pin++);
	}

	return this;
}

ComplexArray^ ComplexArray::operator+(Complex% c)
{
	return this + %c;
}


ComplexArray^ ComplexArray::operator+(Complex^ c)
{
	ComplexArray^ res = gcnew ComplexArray(this->Length, false);
	double * pin = begin();
	double * pout = res->begin();
	double * last = end();
	while(pin != last){
		*(pout++) = *(pin++) + c->Real;
		*(pout++) = *(pin++) + c->Imag;
	}
	return res;
}


ComplexArray^ ComplexArray::operator+(double d)
{
	ComplexArray^ res = gcnew ComplexArray(this->Length, false);
	double * pin = begin();
	double * pout = res->begin();
	double * last = end();
	while(pin != last){
		*(pout++) = *(pin++) + d;  // add only real
		*(pout++) = *(pin++);
	}
	return res;
}

ComplexArray^ ComplexArray::operator+(ComplexArray% ca)
{
	return this + %ca;
}


ComplexArray^ ComplexArray::operator+(ComplexArray^ ca)
{
	if(size_ != ca->size_)
		throw gcnew ArgumentException("Different size");
	ComplexArray^ ans = gcnew ComplexArray(size_, false);

	double* pout = ans->begin();
	double* x = begin();
	double* y = ca->begin();
	while(x != end())
	{
		*(pout++) = *(x++) + *(y++);
	}

	return ans;
}



///////////////////////////////////////////////////////////////////////////////






// Implimentations of operator + 

ComplexArray^ ComplexArray::operator +(double lhs, ComplexArray^ rhs)
{
    return rhs + lhs;
}

ComplexArray^ ComplexArray::operator +(double lhs, ComplexArray% rhs)
{
    return rhs + lhs;
}

ComplexArray^ ComplexArray::operator +(Complex^ lhs, ComplexArray^ rhs)
{
    return rhs + lhs;
}

ComplexArray^ ComplexArray::operator +(Complex^ lhs, ComplexArray% rhs)
{
    return rhs + lhs;
}

ComplexArray^ ComplexArray::operator +(Complex% lhs, ComplexArray^ rhs)
{
    return rhs + lhs;
}

ComplexArray^ ComplexArray::operator +(Complex% lhs, ComplexArray% rhs)
{
    return rhs + lhs;
}

// Implimentations of operator * 

ComplexArray^ ComplexArray::operator *(double rhs)
{
  // Cleate Clone
  ComplexArray^ res = gcnew ComplexArray(size_, false);
  // Apply operation and return
  for(int i = 0; i < Length; ++i){
    res[i] = this[i] * rhs;
  }
  return res;
}

ComplexArray^ ComplexArray::operator *(double lhs, ComplexArray^ rhs)
{
    return rhs * lhs;
}

ComplexArray^ ComplexArray::operator *(double lhs, ComplexArray% rhs)
{
    return rhs * lhs;
}

ComplexArray^ ComplexArray::operator *(Complex^ rhs)
{
  // Cleate Clone
  ComplexArray^ res = gcnew ComplexArray(size_, false);
  // Apply operation and return
  for(int i = 0; i < Length; ++i){
    res[i] = this[i] * rhs;
  }
  return res;
}

ComplexArray^ ComplexArray::operator *(Complex^ lhs, ComplexArray^ rhs)
{
    return rhs * lhs;
}

ComplexArray^ ComplexArray::operator *(Complex^ lhs, ComplexArray% rhs)
{
    return rhs * lhs;
}

ComplexArray^ ComplexArray::operator *(Complex% rhs)
{
  // Cleate Clone
  ComplexArray^ res = gcnew ComplexArray(size_, false);
  // Apply operation and return
  for(int i = 0; i < Length; ++i){
    res[i] = this[i] * rhs;
  }
  return res;
}

ComplexArray^ ComplexArray::operator *(Complex% lhs, ComplexArray^ rhs)
{
    return rhs * lhs;
}

ComplexArray^ ComplexArray::operator *(Complex% lhs, ComplexArray% rhs)
{
    return rhs * lhs;
}

ComplexArray^ ComplexArray::operator *(ComplexArray^ rhs)
{
  // Cleate Clone
  ComplexArray^ res = gcnew ComplexArray(size_, false);
  // Apply operation and return
  for(int i = 0; i < Length; ++i){
    res[i] = this[i] * rhs[i];
  }
  return res;
}

ComplexArray^ ComplexArray::operator *(ComplexArray% rhs)
{
  // Cleate Clone
  ComplexArray^ res = gcnew ComplexArray(size_, false);
  // Apply operation and return
  for(int i = 0; i < Length; ++i){
    res[i] = this[i] * rhs[i];
  }
  return res;
}

ComplexArray^ ComplexArray::operator -(double rhs)
{
  // Cleate Clone
  ComplexArray^ res = gcnew ComplexArray(size_, false);
  // Apply operation and return
  for(int i = 0; i < Length; ++i){
    res[i] = this[i] - rhs;
  }
  return res;
}

ComplexArray^ ComplexArray::operator -(double lhs, ComplexArray^ rhs)
{
  // allocate results without initialization
  ComplexArray^ res = gcnew ComplexArray(rhs->size_, false);
  // Apply operation
  for(int i = 0; i < res->Length; ++i){
    res[i] = lhs - rhs[i];
  }
  return res;
}

ComplexArray^ ComplexArray::operator -(double lhs, ComplexArray% rhs)
{
  // allocate results without initialization
  ComplexArray^ res = gcnew ComplexArray(rhs.size_, false);
  // Apply operation
  for(int i = 0; i < res->Length; ++i){
    res[i] = lhs - rhs[i];
  }
  return res;
}

ComplexArray^ ComplexArray::operator -(Complex^ rhs)
{
  // Cleate Clone
  ComplexArray^ res = gcnew ComplexArray(size_, false);
  // Apply operation and return
  for(int i = 0; i < Length; ++i){
    res[i] = this[i] - rhs;
  }
  return res;
}

ComplexArray^ ComplexArray::operator -(Complex^ lhs, ComplexArray^ rhs)
{
  // allocate results without initialization
  ComplexArray^ res = gcnew ComplexArray(rhs->size_, false);
  // Apply operation
  for(int i = 0; i < res->Length; ++i){
    res[i] = lhs - rhs[i];
  }
  return res;
}

ComplexArray^ ComplexArray::operator -(Complex^ lhs, ComplexArray% rhs)
{
  // allocate results without initialization
  ComplexArray^ res = gcnew ComplexArray(rhs.size_, false);
  // Apply operation
  for(int i = 0; i < res->Length; ++i){
    res[i] = lhs - rhs[i];
  }
  return res;
}

ComplexArray^ ComplexArray::operator -(Complex% rhs)
{
  // Cleate Clone
  ComplexArray^ res = gcnew ComplexArray(size_, false);
  // Apply operation and return
  for(int i = 0; i < Length; ++i){
    res[i] = this[i] - rhs;
  }
  return res;
}

ComplexArray^ ComplexArray::operator -(Complex% lhs, ComplexArray^ rhs)
{
  // allocate results without initialization
  ComplexArray^ res = gcnew ComplexArray(rhs->size_, false);
  // Apply operation
  for(int i = 0; i < res->Length; ++i){
    res[i] = lhs - rhs[i];
  }
  return res;
}

ComplexArray^ ComplexArray::operator -(Complex% lhs, ComplexArray% rhs)
{
  // allocate results without initialization
  ComplexArray^ res = gcnew ComplexArray(rhs.size_, false);
  // Apply operation
  for(int i = 0; i < res->Length; ++i){
    res[i] = lhs - rhs[i];
  }
  return res;
}

ComplexArray^ ComplexArray::operator -(ComplexArray^ rhs)
{
  // Cleate Clone
  ComplexArray^ res = gcnew ComplexArray(size_, false);
  // Apply operation and return
  for(int i = 0; i < Length; ++i){
    res[i] = this[i] - rhs[i];
  }
  return res;
}

ComplexArray^ ComplexArray::operator -(ComplexArray% rhs)
{
  // Cleate Clone
  ComplexArray^ res = gcnew ComplexArray(size_, false);
  // Apply operation and return
  for(int i = 0; i < Length; ++i){
    res[i] = this[i] - rhs[i];
  }
  return res;
}

ComplexArray^ ComplexArray::operator /(double rhs)
{
  // Cleate Clone
  ComplexArray^ res = gcnew ComplexArray(size_, false);
  // Apply operation and return
  for(int i = 0; i < Length; ++i){
    res[i] = this[i] / rhs;
  }
  return res;
}

ComplexArray^ ComplexArray::operator /(double lhs, ComplexArray^ rhs)
{
  // allocate results without initialization
  ComplexArray^ res = gcnew ComplexArray(rhs->size_, false);
  // Apply operation
  for(int i = 0; i < res->Length; ++i){
    res[i] = lhs / rhs[i];
  }
  return res;
}

ComplexArray^ ComplexArray::operator /(double lhs, ComplexArray% rhs)
{
  // allocate results without initialization
  ComplexArray^ res = gcnew ComplexArray(rhs.size_, false);
  // Apply operation
  for(int i = 0; i < res->Length; ++i){
    res[i] = lhs / rhs[i];
  }
  return res;
}

ComplexArray^ ComplexArray::operator /(Complex^ rhs)
{
  // Cleate Clone
  ComplexArray^ res = gcnew ComplexArray(size_, false);
  // Apply operation and return
  for(int i = 0; i < Length; ++i){
    res[i] = this[i] / rhs;
  }
  return res;
}

ComplexArray^ ComplexArray::operator /(Complex^ lhs, ComplexArray^ rhs)
{
  // allocate results without initialization
  ComplexArray^ res = gcnew ComplexArray(rhs->size_, false);
  // Apply operation
  for(int i = 0; i < res->Length; ++i){
    res[i] = lhs / rhs[i];
  }
  return res;
}

ComplexArray^ ComplexArray::operator /(Complex^ lhs, ComplexArray% rhs)
{
  // allocate results without initialization
  ComplexArray^ res = gcnew ComplexArray(rhs.size_, false);
  // Apply operation
  for(int i = 0; i < res->Length; ++i){
    res[i] = lhs / rhs[i];
  }
  return res;
}

ComplexArray^ ComplexArray::operator /(Complex% rhs)
{
  // Cleate Clone
  ComplexArray^ res = gcnew ComplexArray(size_, false);
  // Apply operation and return
  for(int i = 0; i < Length; ++i){
    res[i] = this[i] / rhs;
  }
  return res;
}

ComplexArray^ ComplexArray::operator /(Complex% lhs, ComplexArray^ rhs)
{
  // allocate results without initialization
  ComplexArray^ res = gcnew ComplexArray(rhs->size_, false);
  // Apply operation
  for(int i = 0; i < res->Length; ++i){
    res[i] = lhs / rhs[i];
  }
  return res;
}

ComplexArray^ ComplexArray::operator /(Complex% lhs, ComplexArray% rhs)
{
  // allocate results without initialization
  ComplexArray^ res = gcnew ComplexArray(rhs.size_, false);
  // Apply operation
  for(int i = 0; i < res->Length; ++i){
    res[i] = lhs / rhs[i];
  }
  return res;
}

ComplexArray^ ComplexArray::operator /(ComplexArray^ rhs)
{
  // Cleate Clone
  ComplexArray^ res = gcnew ComplexArray(size_, false);
  // Apply operation and return
  for(int i = 0; i < Length; ++i){
    res[i] = this[i] / rhs[i];
  }
  return res;
}

ComplexArray^ ComplexArray::operator /(ComplexArray% rhs)
{
  // Cleate Clone
  ComplexArray^ res = gcnew ComplexArray(size_, false);
  // Apply operation and return
  for(int i = 0; i < Length; ++i){
    res[i] = this[i] / rhs[i];
  }
  return res;
}


END_NAMESPACE;
