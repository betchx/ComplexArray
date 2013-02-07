using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using ComplexArrayLib;
namespace TestComplexArray
{
    using NUnit.Framework;

    [TestFixture]    
    public class TestComplex
    {
        [Test]
        public void Construct()
        {
            Complex c = new Complex();
            Assert.AreEqual(0.0, c.Real, 0.0001);
            Assert.AreEqual(0.0, c.Imag, 0.0001);
            const double e = 0.0001;
            double r = 387;
            double i = 83.32;
            double v = 97.92;

            c = new Complex(r,i);
            Assert.AreEqual(r, c.Real, e);
            Assert.AreEqual(i, c.Imag, e);

            Complex d = new Complex(c);
            Assert.AreEqual(r, d.Real, e);
            Assert.AreEqual(i, d.Imag, e);

            c = new Complex(v);
            Assert.AreEqual(v, c.Real, e);
            Assert.AreEqual(0.0, c.Imag, e);
        }
    }
}
