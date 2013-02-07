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
        public void Abs()
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

            var r2 = Math.Sqrt(2.0);
            carr.imag_assign(arr);
            res = carr.abs();

            for (int i = 0; i < n; i++)
            {
                Assert.AreEqual(arr[i]*r2, res[i], 0.001);
            }

        }

        [Test]
        public void Power()
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

            carr.imag_assign(arr);
            res = carr.power();

            for (int i = 0; i < n; i++)
            {
                Assert.AreEqual(2*ans[i], res[i], 0.001);
            }

        }
    }
}
