// for header file
    // Definitions of operator +
    ComplexArray^ operator +(double rhs);
    static ComplexArray^ operator +(double lhs, ComplexArray^ rhs);
    static ComplexArray^ operator +(double lhs, ComplexArray% rhs);
    ComplexArray^ operator +(Complex^ rhs);
    static ComplexArray^ operator +(Complex^ lhs, ComplexArray^ rhs);
    static ComplexArray^ operator +(Complex^ lhs, ComplexArray% rhs);
    ComplexArray^ operator +(Complex% rhs);
    static ComplexArray^ operator +(Complex% lhs, ComplexArray^ rhs);
    static ComplexArray^ operator +(Complex% lhs, ComplexArray% rhs);
    ComplexArray^ operator +(ComplexArray^ rhs);
    ComplexArray^ operator +(ComplexArray% rhs);

    // Definitions of operator *
    ComplexArray^ operator *(double rhs);
    static ComplexArray^ operator *(double lhs, ComplexArray^ rhs);
    static ComplexArray^ operator *(double lhs, ComplexArray% rhs);
    ComplexArray^ operator *(Complex^ rhs);
    static ComplexArray^ operator *(Complex^ lhs, ComplexArray^ rhs);
    static ComplexArray^ operator *(Complex^ lhs, ComplexArray% rhs);
    ComplexArray^ operator *(Complex% rhs);
    static ComplexArray^ operator *(Complex% lhs, ComplexArray^ rhs);
    static ComplexArray^ operator *(Complex% lhs, ComplexArray% rhs);
    ComplexArray^ operator *(ComplexArray^ rhs);
    ComplexArray^ operator *(ComplexArray% rhs);

    // Definitions of operator -
    ComplexArray^ operator -(double rhs);
    static ComplexArray^ operator -(double lhs, ComplexArray^ rhs);
    static ComplexArray^ operator -(double lhs, ComplexArray% rhs);
    ComplexArray^ operator -(Complex^ rhs);
    static ComplexArray^ operator -(Complex^ lhs, ComplexArray^ rhs);
    static ComplexArray^ operator -(Complex^ lhs, ComplexArray% rhs);
    ComplexArray^ operator -(Complex% rhs);
    static ComplexArray^ operator -(Complex% lhs, ComplexArray^ rhs);
    static ComplexArray^ operator -(Complex% lhs, ComplexArray% rhs);
    ComplexArray^ operator -(ComplexArray^ rhs);
    ComplexArray^ operator -(ComplexArray% rhs);

    // Definitions of operator /
    ComplexArray^ operator /(double rhs);
    static ComplexArray^ operator /(double lhs, ComplexArray^ rhs);
    static ComplexArray^ operator /(double lhs, ComplexArray% rhs);
    ComplexArray^ operator /(Complex^ rhs);
    static ComplexArray^ operator /(Complex^ lhs, ComplexArray^ rhs);
    static ComplexArray^ operator /(Complex^ lhs, ComplexArray% rhs);
    ComplexArray^ operator /(Complex% rhs);
    static ComplexArray^ operator /(Complex% lhs, ComplexArray^ rhs);
    static ComplexArray^ operator /(Complex% lhs, ComplexArray% rhs);
    ComplexArray^ operator /(ComplexArray^ rhs);
    ComplexArray^ operator /(ComplexArray% rhs);

// for source file

// Implimentations of operator + 

ComplexArray^ ComplexArray::operator +(double rhs)
{
  // Cleate Clone
  ComplexArray^ res = gcnew ComplexArray(size_, false);
  // Apply operation and return
  for(int i = 0; i < Length; ++i){
    res[i] = this[i] + rhs;
  }
  return res;
}

ComplexArray^ ComplexArray::operator +(double lhs, ComplexArray^ rhs)
{
    return rhs + lhs;
}

ComplexArray^ ComplexArray::operator +(double lhs, ComplexArray% rhs)
{
    return rhs + lhs;
}

ComplexArray^ ComplexArray::operator +(Complex^ rhs)
{
  // Cleate Clone
  ComplexArray^ res = gcnew ComplexArray(size_, false);
  // Apply operation and return
  for(int i = 0; i < Length; ++i){
    res[i] = this[i] + rhs;
  }
  return res;
}

ComplexArray^ ComplexArray::operator +(Complex^ lhs, ComplexArray^ rhs)
{
    return rhs + lhs;
}

ComplexArray^ ComplexArray::operator +(Complex^ lhs, ComplexArray% rhs)
{
    return rhs + lhs;
}

ComplexArray^ ComplexArray::operator +(Complex% rhs)
{
  // Cleate Clone
  ComplexArray^ res = gcnew ComplexArray(size_, false);
  // Apply operation and return
  for(int i = 0; i < Length; ++i){
    res[i] = this[i] + rhs;
  }
  return res;
}

ComplexArray^ ComplexArray::operator +(Complex% lhs, ComplexArray^ rhs)
{
    return rhs + lhs;
}

ComplexArray^ ComplexArray::operator +(Complex% lhs, ComplexArray% rhs)
{
    return rhs + lhs;
}

ComplexArray^ ComplexArray::operator +(ComplexArray^ rhs)
{
  // Cleate Clone
  ComplexArray^ res = gcnew ComplexArray(size_, false);
  // Apply operation and return
  for(int i = 0; i < Length; ++i){
    res[i] = this[i] + rhs[i];
  }
  return res;
}

ComplexArray^ ComplexArray::operator +(ComplexArray% rhs)
{
  // Cleate Clone
  ComplexArray^ res = gcnew ComplexArray(size_, false);
  // Apply operation and return
  for(int i = 0; i < Length; ++i){
    res[i] = this[i] + rhs[i];
  }
  return res;
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
