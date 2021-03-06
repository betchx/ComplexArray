#include <complex>
#include <fftw3.h>
#include "namespace.h"
#using "ComplexArray.dll"

#ifdef __INTELLISENSE__
#pragma diag_suppress 2242
#endif

using namespace NUnit::Framework;
using namespace System;
using namespace System::Collections::Generic;

BEGIN_NAMESPACE;

[NUnit::Framework::TestFixture]
ref class TestWaveData
{
public:
  [NUnit::Framework::Test] void Allocation();
  [NUnit::Framework::Test] void CreateByArray();
  [NUnit::Framework::Test] void CreateByFullComplexArray();
  [NUnit::Framework::Test] void CreateByHalfComplexArray();
  [NUnit::Framework::Test] void PulseFFT();
  [NUnit::Framework::Test] void Spectrums();
  [NUnit::Framework::Test] void Wave();
  [NUnit::Framework::Test] void WaveAssign();
  [NUnit::Framework::Test] void Convolution();
  [NUnit::Framework::Test] void Abs();
  [NUnit::Framework::Test] void Power();
  [NUnit::Framework::Test] void Decibel();
};

//Test
void TestWaveData::Allocation()
{
  int n = 10;
  WaveData^ wd = gcnew WaveData(n);
  Assert::AreEqual(n, wd->Length);
}

void TestWaveData::CreateByArray()
{
  array<double>^ arr = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 };
  WaveData wd(arr);
  Assert::AreEqual(arr->Length, wd.Length);
  Assert::False(wd.IsWaveDirty);
  Assert::True(wd.IsSpectrumDirty);
  for (int i = 0; i < arr->Length; ++i)
  {
    Assert::AreEqual(arr[i], wd[i], 0.0001);
  }
}

void TestWaveData::CreateByFullComplexArray()
{
  array<double>^ arr = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 };
  ComplexArray carr(arr);
  WaveData wd(carr);
  Assert::AreEqual(carr.Length, wd.Length);
  Assert::True(wd.IsWaveDirty);
  Assert::False(wd.IsSpectrumDirty);
  Assert::AreEqual(carr.Length / 2 + 1, wd.SpLength);

  // check values
  Assert::AreEqual(1.0, wd.Real[0], 0.001);
  Assert::AreEqual(0.0, wd.Imag[0], 0.001);
  Assert::AreEqual(3.0, wd.Real[1], 0.001);
  Assert::AreEqual(4.0, wd.Imag[1], 0.001);
  Assert::AreEqual(5.0, wd.Real[2], 0.001);
  Assert::AreEqual(0.0, wd.Imag[2], 0.001);
}

void TestWaveData::CreateByHalfComplexArray()
{
  array<double>^ arr = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };
  ComplexArray carr(arr);
  Assert::AreEqual(arr->Length / 2, carr.Length);
  WaveData wd(carr);
  Assert::AreEqual(arr->Length - 2, wd.Length);
  Assert::True(wd.IsWaveDirty);
  Assert::False(wd.IsSpectrumDirty);
  Assert::AreEqual(arr->Length / 2, wd.SpLength);

  // check values
  Assert::AreEqual(1.0, wd.Real[0], 0.001);
  Assert::AreEqual(0.0, wd.Imag[0], 0.001);
  Assert::AreEqual(3.0, wd.Real[1], 0.001);
  Assert::AreEqual(4.0, wd.Imag[1], 0.001);
  Assert::AreEqual(5.0, wd.Real[2], 0.001);
  Assert::AreEqual(6.0, wd.Imag[2], 0.001);
  Assert::AreEqual(7.0, wd.Real[3], 0.001);
  Assert::AreEqual(8.0, wd.Imag[3], 0.001);
  Assert::AreEqual(9.0, wd.Real[4], 0.001);
  Assert::AreEqual(0.0, wd.Imag[4], 0.001);
}

void TestWaveData::PulseFFT()
{
  int n = 8;
  WaveData wd(n);
  wd.ClearWave();
  Assert::False(wd.IsWaveDirty);
  Assert::True(wd.IsSpectrumDirty);

  for (int i = 0; i < n; ++i)
  {
    Assert::AreEqual(0.0, wd[i], 0.0001);
  }

  wd[0] = 1.0;
  Assert::False(wd.IsWaveDirty);
  Assert::True(wd.IsSpectrumDirty);
  wd.Real[0];
  Assert::False(wd.IsWaveDirty);
  Assert::False(wd.IsSpectrumDirty);
  for (int i = 0; i < wd.SpLength; ++i)
  {
    Assert::AreEqual(1.0, wd.Real[i], 0.0001, "Real:" + (i).ToString());
    Assert::AreEqual(0.0, wd.Imag[i], 0.0001, "Imag:" + (i).ToString());
  }
}

void TestWaveData::Wave()
{
  array<double>^ arr = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };
  WaveData wd(arr);
  IEnumerator<double>^ e = wd.Wave->GetEnumerator();

  Assert::AreEqual(arr->Length, System::Linq::Enumerable::Count(wd.Wave));

  Assert::True(e->MoveNext());
  Assert::AreEqual(1.0, e->Current, 0.0001);
  Assert::True(e->MoveNext());
  Assert::AreEqual(2.0, e->Current, 0.0001);
  Assert::True(e->MoveNext());
  Assert::AreEqual(3.0, e->Current, 0.0001);
  Assert::True(e->MoveNext());
  Assert::AreEqual(4.0, e->Current, 0.0001);
  Assert::True(e->MoveNext());
  Assert::AreEqual(5.0, e->Current, 0.0001);
  Assert::True(e->MoveNext());
  Assert::AreEqual(6.0, e->Current, 0.0001);
  Assert::True(e->MoveNext());
  Assert::AreEqual(7.0, e->Current, 0.0001);
  Assert::True(e->MoveNext());
  Assert::AreEqual(8.0, e->Current, 0.0001);
  Assert::True(e->MoveNext());
  Assert::AreEqual(9.0, e->Current, 0.0001);
  Assert::True(e->MoveNext());
  Assert::AreEqual(10.0, e->Current, 0.0001);
  Assert::False(e->MoveNext());
}

void TestWaveData::Spectrums()
{
  array<double>^ arr = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };
  array<double>^ ans = { 1.0, 0.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0,  0.0 };
  ComplexArray carr(arr);
  ComplexArray cans(ans);
  WaveData wd(carr);
  Assert::AreEqual(8, wd.Length);
  Assert::AreEqual(5, wd.SpLength);
  IEnumerator<Complex^>^ ce = cans.GetEnumerator();
  IEnumerator<Complex^>^ we = wd.Spectrums->GetEnumerator();
  Assert::True(ce->MoveNext());
  Assert::True(we->MoveNext());
  Assert::AreEqual(ce->Current->Real, we->Current->Real, 0.000001);
  Assert::AreEqual(ans[0], we->Current->Real, 0.000001);
  Assert::AreEqual(ce->Current->Imag, we->Current->Imag, 0.000001);
  Assert::AreEqual(ans[1], we->Current->Imag, 0.000001);
  Assert::True(ce->MoveNext());
  Assert::True(we->MoveNext());
  Assert::AreEqual(ce->Current->Real, we->Current->Real, 0.000001);
  Assert::AreEqual(ans[2], we->Current->Real, 0.000001);
  Assert::AreEqual(ce->Current->Imag, we->Current->Imag, 0.000001);
  Assert::AreEqual(ans[3], we->Current->Imag, 0.000001);
  Assert::True(ce->MoveNext());
  Assert::True(we->MoveNext());
  Assert::AreEqual(ce->Current->Real, we->Current->Real, 0.000001);
  Assert::AreEqual(ans[4], we->Current->Real, 0.000001);
  Assert::AreEqual(ce->Current->Imag, we->Current->Imag, 0.000001);
  Assert::AreEqual(ans[5], we->Current->Imag, 0.000001);
  Assert::True(ce->MoveNext());
  Assert::True(we->MoveNext());
  Assert::AreEqual(ce->Current->Real, we->Current->Real, 0.000001);
  Assert::AreEqual(ans[6], we->Current->Real, 0.000001);
  Assert::AreEqual(ce->Current->Imag, we->Current->Imag, 0.000001);
  Assert::AreEqual(ans[7], we->Current->Imag, 0.000001);
  Assert::True(ce->MoveNext());
  Assert::True(we->MoveNext());
  Assert::AreEqual(ce->Current->Real, we->Current->Real, 0.000001);
  Assert::AreEqual(ans[8], we->Current->Real, 0.000001);
  Assert::AreEqual(ce->Current->Imag, we->Current->Imag, 0.000001);
  Assert::AreEqual(ans[9], we->Current->Imag, 0.000001);
  Assert::False(ce->MoveNext());
  Assert::False(we->MoveNext());
}

void TestWaveData::WaveAssign()
{
  array<double>^ arr = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 };
  WaveData^ wd = gcnew WaveData(arr->Length);
  wd->Wave = arr;
  for (int i = 0; i < 8; ++i)
  {
    Assert::AreEqual(arr[i], wd[i], 0.00001);
  }

  wd = gcnew WaveData(6);
  wd->Wave = arr;
  for (int i = 0; i < 6; ++i)
  {
    Assert::AreEqual(arr[i], wd[i], 0.0001);
  }
  wd = gcnew WaveData(10);
  wd->ClearWave();
  wd->Wave = arr;
  for (int i = 0; i < 8; ++i)
  {
    Assert::AreEqual(arr[i], wd[i], 0.00001);
  }
  Assert::AreEqual(0.0, wd[8], 0.00001);
  Assert::AreEqual(0.0, wd[9], 0.00001);
}

void TestWaveData::Convolution()
{
  array<double>^ wave = { 1.0,  0.7,  0.0, -0.7, -1.0, -0.7,  0.0,  0.7 };
  array<double>^ tgt = { 0.0,  1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0 };
  array<double>^ answer = { 0.7,  1.0,  0.7,  0.0, -0.7, -1.0, -0.7,  0.0 };
  WaveData^ f = gcnew WaveData(wave);
  WaveData^ g = gcnew WaveData(tgt);
  WaveData^ res = f * g;
  for (int i = 0; i < 8; ++i) {
    Assert::AreEqual(answer[i], res[i], 0.00001, (i).ToString());
  }
}

void TestWaveData::Abs()
{
  using namespace System::Linq;
  array<double>^ real = { -4.0, -3.0, -2.0, -1.0, 0.0, 1.0, 2.0, 3.0, 4.0 };
  int n = real->Length;
  array<double>^ ans = gcnew array<double>(n);
  double rt2 = sqrt(2.0);
  for (int i = 0; i < n; ++i) {
    ans[i] = rt2 * abs(real[i]);
  }

  WaveData^ wd = gcnew WaveData((n - (n % 2)) * 2);
  wd->ClearSpectrum();
  wd->Reals = real;

  array<double>^ res = Enumerable::ToArray(wd->Abs);

  Assert::AreEqual(n, res->Length);

  for (int i = 0; i < n; ++i)
  {
    Assert::AreEqual(fabs(real[i]), res[i], 0.00001, i.ToString());
  }

  wd->Imags = real;
  for (int i = 0; i < n; ++i)
  {
    Assert::AreEqual(real[i], wd->Real[i], 0.0001);
    Assert::AreEqual(real[i], wd->Imag[i], 0.0001);
  }
  res = Enumerable::ToArray(wd->Abs);
  for (int i = 0; i < n; ++i)
  {
    Assert::AreEqual(ans[i], res[i], 0.00001, i.ToString());
  }
}

void TestWaveData::Power()
{
  using namespace System::Linq;
  array<double>^ real = { -4.0, -3.0, -2.0, -1.0, 0.0, 1.0, 2.0, 3.0, 4.0 };
  int n = real->Length;
  array<double>^ ans = gcnew array<double>(n);
  for (int i = 0; i < n; ++i) {
    ans[i] = 2 * real[i] * real[i];
  }

  WaveData^ wd = gcnew WaveData((n - (n % 2)) * 2);
  wd->ClearSpectrum();
  wd->Reals = real;

  array<double>^ res = Enumerable::ToArray(wd->Power);

  Assert::AreEqual(n, res->Length);

  for (int i = 0; i < n; ++i)
  {
    Assert::AreEqual(real[i] * real[i], res[i], 0.00001, i.ToString());
  }

  wd->Imags = real;
  for (int i = 0; i < n; ++i)
  {
    Assert::AreEqual(real[i], wd->Real[i], 0.0001);
    Assert::AreEqual(real[i], wd->Imag[i], 0.0001);
  }
  res = Enumerable::ToArray(wd->Power);
  for (int i = 0; i < n; ++i)
  {
    Assert::AreEqual(ans[i], res[i], 0.00001, i.ToString());
  }
}

void TestWaveData::Decibel()
{
  using namespace System::Linq;
  array<double>^ real = { 0.001,  0.01,   0.1, 1.0, 10.0, 100.0, 1000.0 };
  array<double>^ ans = { -120.0, -80.0, -40.0, 0.0, 40.0,  80.0,  120.0 };
  int n = 7;
  int sz = 12;

  WaveData^ wd = gcnew WaveData(12);
  wd->ClearSpectrum();
  wd->Reals = real;

  array<double>^ res = Enumerable::ToArray(wd->Decibel);

  Assert::AreEqual(n, res->Length);

  for (int i = 0; i < n; ++i)
  {
    Assert::AreEqual(real[i], wd->Real[i], 0.0001);
    Assert::AreEqual(0.0, wd->Imag[i], 0.0001);
  }
  for (int i = 0; i < n; ++i)
  {
    Assert::AreEqual(ans[i], res[i], 0.00001, i.ToString());
  }
}

END_NAMESPACE;
