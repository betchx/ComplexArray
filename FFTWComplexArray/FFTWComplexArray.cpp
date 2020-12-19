//#include "Stdafx.h"
#include "namespace.h"
#include "FFTWComplexArray.h"

using namespace System::Runtime::InteropServices;

BEGIN_NAMESPACE;

FFTWComplexArray::FFTWComplexArray(int length)
{
  data_.cptr = (fftw_complex*)fftw_malloc(length * sizeof(fftw_complex));
  if (data_.cptr)
    length_ = length;
}

FFTWComplexArray::FFTWComplexArray(array<double>^ arr)
{
  int length = (arr->Length / 2);
  data_.ptr = (double*)fftw_malloc(length * sizeof(fftw_complex));
  if (data_.cptr) {
    length_ = length;
    Marshal::Copy(arr, 0, (System::IntPtr)data_.ptr, length * 2);
  }
}

void FFTWComplexArray::clear()
{
  memset(data_.ptr, 0, length_ * sizeof(fftw_complex));
}

FFTWComplexArray::~FFTWComplexArray() {
  fftw_free(data_.cptr);
}

std::complex<double>& FFTWComplexArray::at(int idx) {
  // index check
  if (idx >= length_) throw std::out_of_range(std::to_string(idx) + " exeed upper bound of " + std::to_string((length_ - 1)));
  if (idx < -length_) throw std::out_of_range(std::to_string(idx) + " exeed lower bound of " + std::to_string(-length_));
  // positive index
  if (idx >= 0) return data_.complex[idx];
  // negative index
  return data_.complex[length_ + idx];
}
const std::complex<double>& FFTWComplexArray::at(int idx)const {
  // remove const for DRY principal
  return const_cast<FFTWComplexArray*>(this)->at(idx);
}

void FFTWComplexArray::set(int idx, const double& re, const double& im) {
  complex& c = at(idx);
  c.real(re); c.imag(im);
}

int FFTWComplexArray::normalize(int idx)const
{
  if (idx < 0) idx += (idx / length_ - 1) * -length_;
  return idx % length_;
}

END_NAMESPACE;

