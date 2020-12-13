#pragma once

#include <complex>
#include <fftw3.h>
#include <vector>

class FFTW_Allocator
{
public:
  // type definition
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef std::complex<double>* pointer;
  typedef const std::complex<double>* const_pointer;
  typedef std::complex<double>& reference;
  typedef const std::complex<double>& const_reference;
  typedef std::complex<double> value_type;

  // binding allocator to type U
  template <class U>
  struct rebind
  {
    typedef std::allocator<U> other;
  };

  FFTW_Allocator() throw() {}
  FFTW_Allocator(const std::allocator<value_type>&) throw() {}
  template <class U> FFTW_Allocator(const std::allocator<U>&) throw() {}
  ~FFTW_Allocator() throw() {}

  pointer allocate(size_type num, std::allocator<void>::const_pointer hint = 0)
  {
    return (pointer)(fftw_malloc(num * sizeof(value_type)));
  }

  // Intialize allocated region
  void construct(pointer p, const_reference value)
  {
    new((void*)p) value_type(value);
  }

  void deallocate(pointer p, size_type num)
  {
    fftw_free((fftw_complex*)p);
  }

  // destruction
  void destroy(pointer p)
  {
    p->~value_type();
  }

  pointer address(reference value) const { return &value; }
  const_pointer address(const_reference value) const { return &value; }

  size_type max_size() const throw()
  {
    return std::numeric_limits<size_t>::max() / sizeof(value_type);
  }
};

typedef std::vector<std::complex<double>, FFTW_Allocator> fftw_vector;
