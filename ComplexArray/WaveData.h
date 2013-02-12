#pragma once


#include "ComplexArray.h"
#include "FFTWComplexArray.h"
using namespace NUnit::Framework;

BEGIN_NAMESPACE;

public ref class WaveData
{
	static unsigned last_id_ = 0u;
	static unsigned next_id(){return ++last_id_;}


	double*  wave_;
	FFTWComplexArray* sp_;

	fftw_plan w2s_, s2w_;

	// dirty_flag
	bool dirty_wave_;
	bool dirty_sp_;

	int length_;
	size_t wave_size_;
	size_t   sp_size_;

	unsigned wave_id_;
	unsigned sp_id_;
	void wave_id_update(){ wave_id_ = next_id(); }
	void   sp_id_update(){   sp_id_ = next_id(); }

	void allocate(int size);
	void update_wave();
	void update_sp();
	void wave_updated(){dirty_wave_ = false; dirty_sp_ =  true;  wave_id_update();}
	void   sp_updated(){dirty_wave_ = true;  dirty_sp_ = false;    sp_id_update();}

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

	property int Length{ int get();}
	property int WaveLength { int get();}
	property int SpLength { int get();}
	property Complex^ Spectrum[int]{ Complex^ get(int idx); void set(int idx, Complex^ value);}
	property double default[int]{ double get(int idx); void set(int idx, double value);}
	property double Real[int]{ double get(int idx); void set(int idx, double value);}
	property double Imag[int]{ double get(int idx); void set(int idx, double value);}

	property IEnumerable<Complex^>^  Spectrum{ IEnumerable<Complex^>^ get(); void set(IEnumerable<Complex^>^ e); }
	property IEnumerable<double>^ Wave{ IEnumerable<double>^ get(); void set(IEnumerable<double>^ e);}
	property IEnumerable<double>^ Reals{ IEnumerable<double>^ get(); void set(IEnumerable<double>^ e);}
	property IEnumerable<double>^ Imags{ IEnumerable<double>^ get(); void set(IEnumerable<double>^ e);}

	property IEnumerable<double>^ Abs{ IEnumerable<double>^ get();}
	property IEnumerable<double>^ Ang{ IEnumerable<double>^ get();}
	property IEnumerable<double>^ Power{ IEnumerable<double>^ get();}
	property IEnumerable<double>^ dB{ IEnumerable<double>^ get();}

	property unsigned wave_id{ unsigned get(){return wave_id_;}}
	property unsigned   sp_id{ unsigned get(){return   sp_id_;}}

	void clear_wave();
	void clear_sp();

	bool is_dirty(){ return dirty_wave_ || dirty_sp_;}
	bool update();

	// Convolution
	static WaveData^ operator * (WaveData^ lhs, WaveData^ rhs);


private:
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
		[Test] void WaveAssign();
		[Test] void Convolution();
        [Test] void Abs();
        [Test] void Power();
        [Test] void dB();
	};
};


END_NAMESPACE;
