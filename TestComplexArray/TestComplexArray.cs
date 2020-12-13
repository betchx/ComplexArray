using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ComplexArrayLib;

namespace TestComplexArray
{
    using NUnit.Framework;

    [TestFixture]
    class TestComplexArray
    {
        [Test]
        public void AbsReal()
        {
            int n = 100;
            var arr = new double[n];
            for (int i = 0; i < n; i++)
            {
                arr[i] = 1.0 + i;
            }
            ComplexArray carr = ComplexArray.real(arr);

            var res = carr.abs();
            for (int i = 0; i < n; i++)
            {
                Assert.AreEqual(arr[i], res[i], 0.0000001);
            }
        }

    [Test]
    public void AbsImag()
    {
      int n = 100;
      var arr = new double[n];
      for (int i = 0; i < n; i++)
      {
        arr[i] = 1.0 + i;
      }
      ComplexArray carr = ComplexArray.imag(arr);

      var res = carr.abs();

      for (int i = 0; i < n; i++)
      {
        Assert.AreEqual(arr[i], res[i], 0.0000001);
      }
    }

    [Test]
    public void AbsComplex()
    {
      int n = 100;
      var arr = new double[2*n];
      var ra = new double[n];
      var im = new double[n];
      var ans = new double[n];
      for (int i = 0; i < n; i++)
      {
        arr[2 * i] = ra[i] = 1.0 + i;
        arr[2 * i + 1] = im[i] = 2.0 + i;
        ans[i] = Math.Sqrt(ra[i] * ra[i] + im[i] * im[i]);
      }
      var carr = new ComplexArray(arr);
      var res = carr.abs();

      for (int i = 0; i < n; i++)
      {
        Assert.AreEqual(ans[i], res[i], 0.0000001);
      }
    }


    [Test]
    public void PowerPos()
    {
      int n = 100;
      var arr = new double[n];
      for (int i = 0; i < n; i++)
      {
        arr[i] = 1.0 + i;
      }
      ComplexArray carr = ComplexArray.real(arr);

      var res = carr.power();
      var ans = arr.Select(b => b * b).ToArray();

      for (int i = 0; i < n; i++)
      {
        Assert.AreEqual(ans[i], res[i], 0.0000001);
      }
    }

    [Test]
    public void PowerNeg()
    {
      int n = 100;
      var arr = new double[n];
      for (int i = 0; i < n; i++)
      {
        arr[i] = 1.0 + i;
      }
      var carr = ComplexArray.imag(arr);
      var res = carr.power();
      var ans = arr.Select(b => b * b).ToArray();

      for (int i = 0; i < n; i++)
      {
        Assert.AreEqual(ans[i], res[i], 0.001);
      }

    }
  }
}
