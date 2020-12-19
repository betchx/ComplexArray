#pragma once


[NUnit::Framework::TestFixture]
ref class TestWaveData
{
public:
  [NUnit::Framework::Test] void Allocation();
  [NUnit::Framework::Test] void CreateByArray();
  [NUnit::Framework::Test] void CreateByFullComplexArray();
  [NUnit::Framework::Test] void CreateByHalfComplexArray();
  [NUnit::Framework::Test] void PulseFFT();
  [NUnit::Framework::Test] void Spectrum();
  [NUnit::Framework::Test] void Wave();
  [NUnit::Framework::Test] void WaveAssign();
  [NUnit::Framework::Test] void Convolution();
  [NUnit::Framework::Test] void Abs();
  [NUnit::Framework::Test] void Power();
  [NUnit::Framework::Test] void Decibel();
};

#define TEST_FRIENDS friend class TestWaveData

