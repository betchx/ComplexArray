using ComplexArrayLib;

using System.Collections.Generic;
using System.Linq;

namespace TestComplexArray
{
  using NUnit.Framework;

  [TestFixture]
  class TestWaveData
  {
    [Test]
    public void LengthIsSameToIntArgmentOfConstruction()
    {
      int n = 10;
      WaveData wd = new WaveData(n);

      Assert.AreEqual(n, wd.Length);
    }
    [Test]
    public void LengthIsSameLengthOfArrayForConstruction() {
      const int n = 24;
      double[] arr = new double[n];
      var wd = new WaveData(arr);
      Assert.AreEqual(n, wd.Length);
    }
    [Test]
    public void LengthIsHalfLengthOfFullComplexArrayForCostruction()
    {
      const int n = 10;
      ComplexArray ca = new ComplexArray(2*n, false);
      var wd = new WaveData(ca);
      Assert.AreEqual(n + 1, wd.SpLength);
      Assert.AreEqual(n * 2, wd.Length);
    }

    [Test]
    public void SpectrumIsDirtyJusAfterConstruction()
    {
      var arr = new double[] { 0.0, 1.0, 2.0, 1.0, 0.0, -1.0, -2.0, -1.0 };
      var wd = new WaveData(arr);
      Assert.True(wd.IsSpectrumDirty);
      Assert.True(wd.IsDirty);
    }

    [Test]
    public void SpectrumIsNotDirtyAfterUpdate()
    {
      var arr = new double[] { 0.0, 1.0, 2.0, 1.0, 0.0, -1.0, -2.0, -1.0 };
      var wd = new WaveData(arr);
      Assert.True(wd.Update());
      Assert.False(wd.IsSpectrumDirty);
    }

    [Test]
    public void AllZeroIfConstructedByInt()
    {
      const int n = 8;
      var data = new WaveData(n);
      foreach (var item in data.Wave)
      {
        Assert.AreEqual(0.0, item, 0.001);
      }
    }
    [Test]
    public void ContructionByDoubleArrayAppliedToWave()
    {
      var arr = new double[] {1.0, 2.0, 3.0, 4.0, 5.0, 6.0 };
      var data = new WaveData(arr);
      var n = arr.Length;
      Assert.AreEqual(n, data.Wave.Count());
      for (int i = 0; i < n; i++)
      {
        Assert.AreEqual(arr[i], data.Wave.ElementAt(i));
      }
    }
    [Test]
    public void ConstructionByComplexArrayAppliedToSpecturmData()
    {
      var reals = new double[] { 0.0, 1.0, 2.0, 3.0, 4.0, 3.0, 2.0, 1.0 };
      var len = reals.Length;
      var imags = new double[] { 0.0, 1.0, 2.0, 1.0, 0.0, -1.0, -2.0, -1.0 };
      var carr = new ComplexArray(reals, imags);
      Assert.AreEqual(len, carr.Length);
      var data = new WaveData(carr);
      var sp_len = len / 2 + 1;

      Assert.AreEqual(sp_len, data.Reals.Count());
      Assert.AreEqual(sp_len, data.Imags.Count());
      Assert.AreEqual(len, data.Wave.Count());

      for (int i = 0; i < sp_len; i++)
      {
        Assert.AreEqual(reals[i], data.Reals.ElementAt(i), 0.0001);
        Assert.AreEqual(imags[i], data.Imags.ElementAt(i), 0.0001);
        Assert.AreEqual(reals[i], data.Spectrums.ElementAt(i).Real);
        Assert.AreEqual(imags[i], data.Spectrums.ElementAt(i).Imag);
      }
    }

  }
}
