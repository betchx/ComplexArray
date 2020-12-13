using ComplexArrayLib;

namespace TestComplexArray
{
  using NUnit.Framework;

  [TestFixture]
  class TestWaveData
  {
    [Test]
    public void Construction()
    {
      int n = 10;
      WaveData wd = new WaveData(n);

      Assert.AreEqual(n, wd.Length);

      n = 24;
      double[] arr = new double[n];
      wd = new WaveData(arr);
      Assert.AreEqual(n, wd.Length);

      n = 20;
      ComplexArray ca = new ComplexArray(n, false);
      wd = new WaveData(ca);

      Assert.AreEqual(n + 1, wd.SpLength);
      Assert.AreEqual(n * 2, wd.Length);
    }
  }
}
