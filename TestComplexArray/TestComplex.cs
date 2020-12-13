using ComplexArrayLib;
namespace TestComplexArray
{
  using NUnit.Framework;

  [TestFixture]
  public class TestComplex
  {
    const double EPS = 1e-10;

    [Test]
    public void Construction()
    {
      Complex c = new Complex();
      Assert.AreEqual(0.0, c.Real, 0.0001);
      Assert.AreEqual(0.0, c.Imag, 0.0001);
      double r = 387;
      double i = 83.32;
      double v = 97.92;

      c = new Complex(r, i);
      Assert.AreEqual(r, c.Real, EPS);
      Assert.AreEqual(i, c.Imag, EPS);

      Complex d = new Complex(c);
      Assert.AreEqual(r, d.Real, EPS);
      Assert.AreEqual(i, d.Imag, EPS);

      c = new Complex(v);
      Assert.AreEqual(v, c.Real, EPS);
      Assert.AreEqual(0.0, c.Imag, EPS);
    }

    [Test]
    public void Construction2()
    {
      Complex c = new Complex();
      Assert.AreEqual(0.0, c.Real, EPS);
      Assert.AreEqual(0.0, c.Imag, EPS);

      const double c_r = 2.3;
      const double c_i = 5.2;

      c = new Complex(c_r);
      Assert.AreEqual(c_r, c.Real, EPS);
      Assert.AreEqual(0.0, c.Imag, EPS);

      c = new Complex(c_r, c_i);

      Assert.AreEqual(c_r, c.Real, EPS);
      Assert.AreEqual(c_i, c.Imag, EPS);
    }

    [Test]
    public void Addition()
    {
      Complex c = new Complex();
      double d_r = 4.3, d_i = 28.3;

      Complex a = c + d_r;
      Assert.AreEqual(d_r, a.Real, EPS);
      Assert.AreEqual(0.0, a.Imag, EPS);

      Complex o = new Complex(d_r, d_i);
      a = c + o;
      Assert.AreEqual(d_r, a.Real, EPS);
      Assert.AreEqual(d_i, a.Imag, EPS);

    }
  }
}
