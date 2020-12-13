#include "Stdafx.h"
#include "ComplexArray.h"

BEGIN_NAMESPACE;

/////////////////////////////////
// Implimentations of operator + 

ComplexArray^ ComplexArray::operator +(ComplexArray^ lhs, double rhs)
{
  // allocate results without initialization
  ComplexArray^ res = gcnew ComplexArray(lhs->size_ / 2, false);
  // Apply operation and return
  for (int i = 0; i < lhs->Length; ++i) {
    res[i] = lhs[i] + rhs;
  }
  return res;
}

ComplexArray^ ComplexArray::operator +(double lhs, ComplexArray^ rhs)
{
  return rhs + lhs;
}

ComplexArray^ ComplexArray::operator +(ComplexArray^ lhs, Complex^ rhs)
{
  // allocate results without initialization
  ComplexArray^ res = gcnew ComplexArray(lhs->size_ / 2, false);
  // Apply operation and return
  for (int i = 0; i < lhs->Length; ++i) {
    res[i] = lhs[i] + rhs;
  }
  return res;
}

ComplexArray^ ComplexArray::operator +(Complex^ lhs, ComplexArray^ rhs)
{
  return rhs + lhs;
}

ComplexArray^ ComplexArray::operator +(ComplexArray^ lhs, ComplexArray^ rhs)
{
  // Size Check
  if (lhs->size_ != rhs->size_) throw gcnew ArgumentException("Need same length ComplexArrays.");
  // allocate results without initialization
  ComplexArray^ res = gcnew ComplexArray(lhs->size_ / 2, false);
  // Apply operation and return
  for (int i = 0; i < lhs->Length; ++i) {
    res[i] = lhs[i] + rhs[i];
  }
  return res;
}

/////////////////////////////////
// Implimentations of operator * 

ComplexArray^ ComplexArray::operator *(ComplexArray^ lhs, double rhs)
{
  // allocate results without initialization
  ComplexArray^ res = gcnew ComplexArray(lhs->size_ / 2, false);
  // Apply operation and return
  for (int i = 0; i < lhs->Length; ++i) {
    res[i] = lhs[i] * rhs;
  }
  return res;
}

ComplexArray^ ComplexArray::operator *(double lhs, ComplexArray^ rhs)
{
  return rhs * lhs;
}

ComplexArray^ ComplexArray::operator *(ComplexArray^ lhs, Complex^ rhs)
{
  // allocate results without initialization
  ComplexArray^ res = gcnew ComplexArray(lhs->size_ / 2, false);
  // Apply operation and return
  for (int i = 0; i < lhs->Length; ++i) {
    res[i] = lhs[i] * rhs;
  }
  return res;
}

ComplexArray^ ComplexArray::operator *(Complex^ lhs, ComplexArray^ rhs)
{
  return rhs * lhs;
}

ComplexArray^ ComplexArray::operator *(ComplexArray^ lhs, ComplexArray^ rhs)
{
  // Size Check
  if (lhs->size_ != rhs->size_) throw gcnew ArgumentException("Need same length ComplexArrays.");
  // allocate results without initialization
  ComplexArray^ res = gcnew ComplexArray(lhs->size_ / 2, false);
  // Apply operation and return
  for (int i = 0; i < lhs->Length; ++i) {
    res[i] = lhs[i] * rhs[i];
  }
  return res;
}

/////////////////////////////////
// Implimentations of operator -

ComplexArray^ ComplexArray::operator -(ComplexArray^ lhs, double rhs)
{
  // allocate results without initialization
  ComplexArray^ res = gcnew ComplexArray(lhs->size_ / 2, false);
  // Apply operation and return
  for (int i = 0; i < lhs->Length; ++i) {
    res[i] = lhs[i] - rhs;
  }
  return res;
}

ComplexArray^ ComplexArray::operator -(double lhs, ComplexArray^ rhs)
{
  // allocate results without initialization
  ComplexArray^ res = gcnew ComplexArray(rhs->size_ / 2, false);
  // Apply operation
  for (int i = 0; i < res->Length; ++i) {
    res[i] = lhs - rhs[i];
  }
  return res;
}

ComplexArray^ ComplexArray::operator -(ComplexArray^ lhs, Complex^ rhs)
{
  // allocate results without initialization
  ComplexArray^ res = gcnew ComplexArray(lhs->size_ / 2, false);
  // Apply operation and return
  for (int i = 0; i < lhs->Length; ++i) {
    res[i] = lhs[i] - rhs;
  }
  return res;
}

ComplexArray^ ComplexArray::operator -(Complex^ lhs, ComplexArray^ rhs)
{
  // allocate results without initialization
  ComplexArray^ res = gcnew ComplexArray(rhs->size_ / 2, false);
  // Apply operation
  for (int i = 0; i < res->Length; ++i) {
    res[i] = lhs - rhs[i];
  }
  return res;
}

ComplexArray^ ComplexArray::operator -(ComplexArray^ lhs, ComplexArray^ rhs)
{
  // Size Check
  if (lhs->size_ != rhs->size_) throw gcnew ArgumentException("Need same length ComplexArrays.");
  // allocate results without initialization
  ComplexArray^ res = gcnew ComplexArray(lhs->size_ / 2, false);
  // Apply operation and return
  for (int i = 0; i < lhs->Length; ++i) {
    res[i] = lhs[i] - rhs[i];
  }
  return res;
}

/////////////////////////////////
// Implimentations of operator /

ComplexArray^ ComplexArray::operator /(ComplexArray^ lhs, double rhs)
{
  // allocate results without initialization
  ComplexArray^ res = gcnew ComplexArray(lhs->size_ / 2, false);
  // Apply operation and return
  for (int i = 0; i < lhs->Length; ++i) {
    res[i] = lhs[i] / rhs;
  }
  return res;
}

ComplexArray^ ComplexArray::operator /(double lhs, ComplexArray^ rhs)
{
  // allocate results without initialization
  ComplexArray^ res = gcnew ComplexArray(rhs->size_ / 2, false);
  // Apply operation
  for (int i = 0; i < res->Length; ++i) {
    res[i] = lhs / rhs[i];
  }
  return res;
}

ComplexArray^ ComplexArray::operator /(ComplexArray^ lhs, Complex^ rhs)
{
  // allocate results without initialization
  ComplexArray^ res = gcnew ComplexArray(lhs->size_ / 2, false);
  // Apply operation and return
  for (int i = 0; i < lhs->Length; ++i) {
    res[i] = lhs[i] / rhs;
  }
  return res;
}

ComplexArray^ ComplexArray::operator /(Complex^ lhs, ComplexArray^ rhs)
{
  // allocate results without initialization
  ComplexArray^ res = gcnew ComplexArray(rhs->size_ / 2, false);
  // Apply operation
  for (int i = 0; i < res->Length; ++i) {
    res[i] = lhs / rhs[i];
  }
  return res;
}

ComplexArray^ ComplexArray::operator /(ComplexArray^ lhs, ComplexArray^ rhs)
{
  // Size Check
  if (lhs->size_ != rhs->size_) throw gcnew ArgumentException("Need same length ComplexArrays.");
  // allocate results without initialization
  ComplexArray^ res = gcnew ComplexArray(lhs->size_ / 2, false);
  // Apply operation and return
  for (int i = 0; i < lhs->Length; ++i) {
    res[i] = lhs[i] / rhs[i];
  }
  return res;
}

END_NAMESPACE;
