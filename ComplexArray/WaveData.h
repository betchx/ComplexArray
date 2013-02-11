#pragma once


#include "ComplexArray.h"
#include "FFTWComplexArray.h"
using namespace NUnit::Framework;

BEGIN_NAMESPACE;

public ref class WaveData
{
	double*  wave_;
	FFTWComplexArray* sp_;

	fftw_plan w2s_, s2w_;

	// dirty_flag
	bool dirty_wave_;
	bool dirty_sp_;

	int length_;
	size_t wave_size_;
	size_t   sp_size_;

	void allocate(int size);
	void update_wave();
	void update_sp();
	void wave_updated(){dirty_wave_ = false; dirty_sp_ = true;}
	void   sp_updated(){dirty_wave_ = true;  dirty_sp_ = false;}

	property std::complex<double>& sp[int]{
		std::complex<double>& get(int idx);
		void set(int idx, std::complex<double>& value);
	}

public:
	WaveData(int size);
	WaveData(array<double>^ arr);
	WaveData(ComplexArray^ carr);
	WaveData(WaveData^ other);

public protected: // only in c++/cli
	WaveData(FFTWComplexArray* carr);
	WaveData(std::complex<double>* begin, std::complex<double>* end);
	WaveData(double* begin, double* end);
	WaveData();

	double * begin(){return wave_;}
	double * end(){return wave_ + length_;}

public:
	virtual ~WaveData(void);

	property int Length {  int get();}
	property int WaveLength {  int get();}
	property int SpLength {  int get();}
	property double Wave[int]{ double get(int idx); void set(int idx, double value);}
	property double Real[int]{ double get(int idx); void set(int idx, double value);}
	property double Imag[int]{ double get(int idx); void set(int idx, double value);}

	property IEnumerable<ComplexView^>^  Spectrum{ IEnumerable<ComplexView^>^ get(); }
	property IEnumerable<double>^ Wave{ IEnumerable<double>^ get();}
	property IEnumerable<double>^ Real{ IEnumerable<double>^ get();}
	property IEnumerable<double>^ Imag{ IEnumerable<double>^ get();}


	void clear_wave();
	void clear_sp();


	// Convolution
	static WaveData^ operator * (WaveData^ lhs, WaveData^ rhs);

protected private:
	[TestFixture] // ref class can contain test
	ref class Test{
	public:
		[Test] void Allocation();
		[Test] void CreateByArray();
		[Test] void CreateByFullComplexArray();
		[Test] void CreateByHalfComplexArray();
		[Test] void PulseFFT();
		[Test] void Spectrum();
		[Test] void Wave();
	};
};


END_NAMESPACE;
