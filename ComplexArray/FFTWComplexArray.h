#pragma once

#include "ComplexArray.h"
#include <fftw3.h>

BEGIN_NAMESPACE;

ref class TestFFTWComplexArray;

class FFTWComplexArray
{
public:
  typedef std::complex<double> complex;
  typedef std::complex<double> data_type;
  typedef std::complex<double>* iterator;
  typedef const std::complex<double>* const_iterator;

private:
  union FFTW_Complex_Ptr
  {
    double* ptr;
    fftw_complex *cptr;
    std::complex<double> *complex;
  } data_;

  friend ref class TestFFTWComplexArray;
  int length_;

public:
  FFTWComplexArray(int length);
  FFTWComplexArray(array<double>^ arr);
  virtual ~FFTWComplexArray();

  void clear();

  std::complex<double>& at(int idx);
  const std::complex<double>& at(int idx)const;
  void set(int idx, const std::complex<double>& val) { at(idx) = val; }
  void set(int idx, const double& re, const double& im);
  int size() { return length_; }

private:
  int normalize(int idx)const;

public:
  // Indexer
  std::complex<double>& operator[](int idx) { return data_.complex[normalize(idx)]; }
  const std::complex<double>& operator[](int idx) const { return data_.complex[normalize(idx)]; }

  // accsesser for fftw (used by fftw_plan functions)
  fftw_complex* fftw() { return data_.cptr; }
  operator fftw_complex* () { return data_.cptr; }

  // iterator as complex array
  iterator begin() { return data_.complex; }
  const_iterator begin()const { return data_.complex; }
  iterator   end() { return data_.complex + length_; }
  const_iterator   end()const { return data_.complex + length_; }

  // iterator for raw double aray
  double* dbl_begin() { return data_.ptr; }
  const double* dbl_begin()const { return data_.ptr; }
  double* dbl_end() { return data_.ptr + length_; }
  const double* dbl_end()  const { return data_.ptr + length_; }
};

END_NAMESPACE;
