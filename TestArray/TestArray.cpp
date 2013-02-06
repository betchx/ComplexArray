// TestArray.cpp : メイン プロジェクト ファイルです。

#include "stdafx.h"
//#include <ComplexArray.h>
#include <cmath>
#include <complex>
#include <random>

using namespace System;
using namespace ComplexArrayLib;
using namespace System::Linq;
using namespace System::Collections::Generic;


#define ASSERT(cond,msg) if(cond){ Console::Write("."); }else{ Console::WriteLine(L"\nERROR: {0}",(msg));}
#define IN_DELTA(val, expect, delta, msg) \
	if(fabs((val) - (expect))<(delta)){ Console::Write("."); \
	}else{ Console::WriteLine(L"\nERROR: {0}.\n {1} expected {2} within {3} but {4}",msg, #val, expect, delta, val);}
#define DBL_EQUAL(val, expect, msg) \
	IN_DELTA(val, expect, 1E-10, msg)
#define ENTER(func) Console::Write(L"\nTest : {0} :", func)

void test_basic()
{
	ENTER(L"Basic");
	array<double>^ arr = {0.0, 1.0, 2.0, 3.0};

	ComplexArray ca(arr);

	Complex^ c0 = ca[0];

	ASSERT(c0->Real == 0.0, L"c0 is not 0.0");

	ASSERT(ca.Length == 2, L"Length error");

	arr[0] = 5.0;
	ASSERT(c0->Real == 0.0, L"copy error");

	c0->Real = 4.0;
	ASSERT(abs(ca[0]->Real - 4.0) < 0.001, L"Reference Error");
}

void test_real_construction()
{
	ENTER(L"Real Construction");
	array<double>^ arr = {0.0, 1.0, 2.0, 3.0};
	ComplexArray^ ra = ComplexArray::real(arr);
	ASSERT(ra->Length == arr->Length, L"Error in length of ComplexArray from real array");
	for(int i = 0; i < arr->Length; i++){
		ASSERT(abs(ra[i]->Real - arr[i]) < 0.001, L"Error in real construction");
		//    Console::WriteLine(L"{0}: {1} => ({2}, {3})", i, arr[i], ra[i]->Real, ra[i]->Imag);
	}
	delete ra;
}

void test_imag_construction()
{
	ENTER(L"Imag Construction");
	array<double>^ arr = {0.0, 1.0, 2.0, 3.0};

	ComplexArray^ ia = ComplexArray::imag(arr);
	ASSERT(ia->Length == arr->Length, L"Error in length of ComplexArray from real array");
	for(int i = 0; i < arr->Length; i++){
		ASSERT(abs(ia[i]->Imag - arr[i]) < 0.001, L"Error in imag construction");
		//    Console::WriteLine(L"{0}: {1} => ({2}, {3})", i, arr[i], ra[i]->Real, ra[i]->Imag);
	}
	delete ia;
}

void test_real_enumerator()
{
	ENTER(L"Real Enumerator");
	array<double>^ arr = {0.0, 1.0, 2.0, 3.0};

	ComplexArray ca(arr);

	IEnumerator<double>^ e = ca.Real;

	ASSERT(e->MoveNext(), L"Real Enumerator: First Move Next");
	IN_DELTA(e->Current, arr[0], 0.001, "First Element");
	ASSERT(e->MoveNext(), L"Real Enumerator: Second Move Next");
	IN_DELTA(e->Current, arr[2], 0.001, "Second Element");
	ASSERT(!e->MoveNext(), L"Real Enumerator termination");
}

void test_imag_enumerator()
{
	ENTER(L"Imag Enumerator");
	array<double>^ arr = {0.0, 1.0, 2.0, 3.0};

	ComplexArray ca(arr);

	IEnumerator<double>^ e = ca.Imag;

	ASSERT(e->MoveNext(), L"Real Enumerator: First Move Next");
	IN_DELTA(e->Current, arr[1], 0.001, "First Element");
	ASSERT(e->MoveNext(), L"Real Enumerator: Second Move Next");
	IN_DELTA(e->Current, arr[3], 0.001, "Second Element");
	ASSERT(!e->MoveNext(), L"Real Enumerator termination");
}

void test_operator_plus_equal_double()
{
	ENTER(L"OP += double");
	array<double>^ arr = {0.0, 1.0, 2.0, 3.0};

	ComplexArray ca(arr);

	ca += 5.0;

	IN_DELTA(ca[0]->Real, 5.0, 0.001, "");
	IN_DELTA(ca[0]->Imag, 1.0, 0.001, "");
	IN_DELTA(ca[1]->Real, 7.0, 0.001, "");
	IN_DELTA(ca[1]->Imag, 3.0, 0.001, "");
}

void test_operator_plus_double()
{
	ENTER(L"OP + double");
	array<double>^ arr = {0.0, 1.0, 2.0, 3.0};

	ComplexArray ca0(arr);

	ComplexArray^ ca =  ca0 + 5.0;

	IN_DELTA(ca[0]->Real, 5.0, 0.001, "Return");
	IN_DELTA(ca[0]->Imag, 1.0, 0.001, "Return");
	IN_DELTA(ca[1]->Real, 7.0, 0.001, "Return");
	IN_DELTA(ca[1]->Imag, 3.0, 0.001, "Return");

	IN_DELTA(ca0[0]->Real, 0.0, 0.001, "Operand");
	IN_DELTA(ca0[0]->Imag, 1.0, 0.001, "Operand");
	IN_DELTA(ca0[1]->Real, 2.0, 0.001, "Operand");
	IN_DELTA(ca0[1]->Imag, 3.0, 0.001, "Operand");
}

void test_operator_plus_equal_complex()
{
	ENTER(L"OP += Complex");
	array<double>^ arr = {0.0, 1.0, 2.0, 3.0};

	ComplexArray ca(arr);

	Complex c(5.0, -5.0);

	ca += c;
	IN_DELTA(ca[0]->Real, 0.0+5.0, 0.001, "");
	IN_DELTA(ca[0]->Imag, 1.0-5.0, 0.001, "");
	IN_DELTA(ca[1]->Real, 2.0+5.0, 0.001, "");
	IN_DELTA(ca[1]->Imag, 3.0-5.0, 0.001, "");
}

void test_operator_plus_complex()
{
	ENTER(L"OP + Complex");
	array<double>^ arr = {0.0, 1.0, 2.0, 3.0};

	ComplexArray ca0(arr);
	Complex c(5.0, -5.0);
	ComplexArray^ ca =  ca0 + c;

	IN_DELTA(ca[0]->Real, 0.0+5.0, 0.001, "Return");
	IN_DELTA(ca[0]->Imag, 1.0-5.0, 0.001, "Return");
	IN_DELTA(ca[1]->Real, 2.0+5.0, 0.001, "Return");
	IN_DELTA(ca[1]->Imag, 3.0-5.0, 0.001, "Return");

	IN_DELTA(ca0[0]->Real, 0.0, 0.001, "Operand");
	IN_DELTA(ca0[0]->Imag, 1.0, 0.001, "Operand");
	IN_DELTA(ca0[1]->Real, 2.0, 0.001, "Operand");
	IN_DELTA(ca0[1]->Imag, 3.0, 0.001, "Operand");
}

void test_complex()
{
	ENTER(L"Complex");

	Complex^ c;

	c = gcnew Complex();
	DBL_EQUAL(c->Real, 0.0, "Default Constcuter Real");
	DBL_EQUAL(c->Imag, 0.0, "Default Constcuter Imag");

	delete c;

	c = gcnew Complex(3.0, 4.0);

	IN_DELTA(c->Real, 3.0, 0.001, "Real");
	IN_DELTA(c->Imag, 4.0, 0.001, "Imag");
	IN_DELTA(c->Power, 25.0, 0.001, "Power");
	IN_DELTA(c->Abs, 5.0, 0.001, "Abs");

	delete c;

	c = gcnew Complex(0.0, 1.0);
	IN_DELTA(c->Ang, Math::PI / 2.0, 0.001, "Ang(0,1)");
	c->Real = 1.0;
	c->Imag = -1.0;
	IN_DELTA(c->Ang, -Math::PI / 4.0, 0.001, "Ang(1,1)");

	Complex^ d = c->Conj;
	IN_DELTA(d->Real, c->Real, 0.001, "Conj(Real)");
	IN_DELTA(d->Imag, -c->Imag, 0.001, "Conj(Imag)");

	delete c;





}

void test_complex_add()
{
	ENTER("COMPLEX ADD");

	double c_r = 1.0, c_i = 2.0;
	double r_r = 7.0, r_i = -5.0;
	double o_r = 3.0, o_i = 6.0;
	double d = 2.0;

	Complex^ c, ^a, ^o, r(r_r, r_i);
	c = gcnew Complex(c_r, c_i);
	o = gcnew Complex(o_r, o_i);

	a = c + d;
	DBL_EQUAL(a->Real, c_r + d, "Real @ dobule");
	DBL_EQUAL(a->Imag, c_i    , "Imag @ double");

	a = d + c;
	DBL_EQUAL(a->Real, c_r + d, "Real @ dobule+");
	DBL_EQUAL(a->Imag, c_i    , "Imag @ double+");

	a = c + o;
	DBL_EQUAL(a->Real, c_r + o_r, "Real @ Complex^");
	DBL_EQUAL(a->Imag, c_i + o_i, "Imag @ Complex^");

	a = c + r;
	DBL_EQUAL(a->Real, c_r + r_r, "Real @ Complex%");
	DBL_EQUAL(a->Imag, c_i + r_i, "Imag @ Complex%");

	std::mt19937 mt(762u);
	size_t mid = (mt.max() - mt.min() ) /2;
	double amp = 1500.0 / mid;

	for(int i = 0; i < 10; i++)
	{
		c_r = amp * (mt() - mid);
		c_i = amp * (mt() - mid);
		o_r = amp * (mt() - mid);
		o_i = amp * (mt() - mid);
		r_r = amp * (mt() - mid);
		r_i = amp * (mt() - mid);

		c->Real = c_r;
		c->Imag = c_i;
		o->Real = o_r;
		o->Imag = o_i;
		r.Real = r_r;
		r.Imag = r_i;

		a = c + r_i;
		DBL_EQUAL(a->Real, c_r + r_i, "Real @ dobule (rand)");
		DBL_EQUAL(a->Imag, c_i      , "Imag @ double (rand)");

		a = o_i + c;
		DBL_EQUAL(a->Real, c_r + o_i, "Real @ dobule +(rand)");
		DBL_EQUAL(a->Imag, c_i      , "Imag @ double +(rand)");

		a = c + o;
		DBL_EQUAL(a->Real, c_r + o_r, "Real @ Complex^ (rand)");
		DBL_EQUAL(a->Imag, c_i + o_i, "Imag @ Complex^ (rand)");

		a = c + r;
		DBL_EQUAL(a->Real, c_r + r_r, "Real @ Complex% (rand)");
		DBL_EQUAL(a->Imag, c_i + r_i, "Imag @ Complex% (rand)");
	}
}

void test_complex_ref_add()
{
	ENTER("Complex Ref ADD");
	double c_r = 21.0, c_i = 22.0;
	double r_r = 67.0, r_i = -53.0;
	double o_r = 83.0, o_i = 64.0;
	double d = 82.0;

	Complex ^a, ^o, c(c_r, c_i), r(r_r, r_i);
	o = gcnew Complex(o_r, o_i);

	a = c + d;
	DBL_EQUAL(a->Real, c_r + d, "Real @ dobule");
	DBL_EQUAL(a->Imag, c_i    , "Imag @ double");

	a = d + c;
	DBL_EQUAL(a->Real, c_r + d, "Real @ dobule+");
	DBL_EQUAL(a->Imag, c_i    , "Imag @ double+");

	a = c + o;
	DBL_EQUAL(a->Real, c_r + o_r, "Real @ Complex^");
	DBL_EQUAL(a->Imag, c_i + o_i, "Imag @ Complex^");

	a = c + r;
	DBL_EQUAL(a->Real, c_r + r_r, "Real @ Complex%");
	DBL_EQUAL(a->Imag, c_i + r_i, "Imag @ Complex%");

	std::mt19937 mt(762u);
	size_t mid = (mt.max() - mt.min() ) /2;
	double amp = 1500.0 / mid;

	for(int i = 0; i < 10; i++)
	{
		c_r = amp * (mt() - mid);
		c_i = amp * (mt() - mid);
		o_r = amp * (mt() - mid);
		o_i = amp * (mt() - mid);
		r_r = amp * (mt() - mid);
		r_i = amp * (mt() - mid);

		c.Real = c_r;
		c.Imag = c_i;
		o->Real = o_r;
		o->Imag = o_i;
		r.Real = r_r;
		r.Imag = r_i;

		a = c + d;
		DBL_EQUAL(a->Real, c_r + d, "Real @ dobule (rand)");
		DBL_EQUAL(a->Imag, c_i    , "Imag @ double (rand)");

		a = d + c;
		DBL_EQUAL(a->Real, c_r + d, "Real @ dobule+ (rand)");
		DBL_EQUAL(a->Imag, c_i    , "Imag @ double+ (rand)");

		a = c + o;
		DBL_EQUAL(a->Real, c_r + o_r, "Real @ Complex^ (rand)");
		DBL_EQUAL(a->Imag, c_i + o_i, "Imag @ Complex^ (rand)");

		a = c + r;
		DBL_EQUAL(a->Real, c_r + r_r, "Real @ Complex% (rand)");
		DBL_EQUAL(a->Imag, c_i + r_i, "Imag @ Complex% (rand)");
	}

}


void test_complex_sub()
{
	ENTER("COMPLEX SUB");

	double c_r = 1.0, c_i = 2.0;
	double r_r = 7.0, r_i = -5.0;
	double o_r = 3.0, o_i = 6.0;
	double d = 2.0;

	Complex^ c, ^a, ^o, r(r_r, r_i);
	c = gcnew Complex(c_r, c_i);
	o = gcnew Complex(o_r, o_i);

	a = c - r_i;
	DBL_EQUAL(a->Real, c_r - r_i, "Real @ dobule (rand)");
	DBL_EQUAL(a->Imag, c_i      , "Imag @ double (rand)");

	a = o_i - c;
	DBL_EQUAL(a->Real, o_i -  c_r, "Real @ dobule- (rand)");
	DBL_EQUAL(a->Imag,      - c_i, "Imag @ double- (rand)");

	a = c - o;
	DBL_EQUAL(a->Real, c_r - o_r, "Real @ Complex^ (rand)");
	DBL_EQUAL(a->Imag, c_i - o_i, "Imag @ Complex^ (rand)");

	a = c - r;
	DBL_EQUAL(a->Real, c_r - r_r, "Real @ Complex% (rand)");
	DBL_EQUAL(a->Imag, c_i - r_i, "Imag @ Complex% (rand)");


	std::mt19937 mt(762u);
	size_t mid = (mt.max() - mt.min() ) /2;
	double amp = 1500.0 / mid;

	for(int i = 0; i < 10; i++)
	{
		c_r = amp * (mt() - mid);
		c_i = amp * (mt() - mid);
		o_r = amp * (mt() - mid);
		o_i = amp * (mt() - mid);
		r_r = amp * (mt() - mid);
		r_i = amp * (mt() - mid);

		c->Real = c_r;
		c->Imag = c_i;
		o->Real = o_r;
		o->Imag = o_i;
		r.Real = r_r;
		r.Imag = r_i;

		a = c - r_i;
		DBL_EQUAL(a->Real, c_r - r_i, "Real @ dobule (rand)");
		DBL_EQUAL(a->Imag, c_i      , "Imag @ double (rand)");

		a = o_i - c;
		DBL_EQUAL(a->Real, -c_r + o_i, "Real @ dobule- (rand)");
		DBL_EQUAL(a->Imag, -c_i      , "Imag @ double- (rand)");

		a = c - o;
		DBL_EQUAL(a->Real, c_r - o_r, "Real @ Complex^ (rand)");
		DBL_EQUAL(a->Imag, c_i - o_i, "Imag @ Complex^ (rand)");

		a = c - r;
		DBL_EQUAL(a->Real, c_r - r_r, "Real @ Complex% (rand)");
		DBL_EQUAL(a->Imag, c_i - r_i, "Imag @ Complex% (rand)");
	}
}

void test_complex_ref_sub()
{
	ENTER("Complex Ref ADD");
	double c_r = 21.0, c_i = 22.0;
	double r_r = 67.0, r_i = -53.0;
	double o_r = 83.0, o_i = 64.0;
	double d = 82.0;

	Complex ^a, ^o, c(c_r, c_i), r(r_r, r_i);
	o = gcnew Complex(o_r, o_i);

	a = c - d;
	DBL_EQUAL(a->Real, c_r - d, "Real @ dobule");
	DBL_EQUAL(a->Imag, c_i    , "Imag @ double");

	a = d - c;
	DBL_EQUAL(a->Real, -c_r + d, "Real @ dobule-");
	DBL_EQUAL(a->Imag, -c_i    , "Imag @ double-");

	a = c - o;
	DBL_EQUAL(a->Real, c_r - o_r, "Real @ Complex^");
	DBL_EQUAL(a->Imag, c_i - o_i, "Imag @ Complex^");

	a = c - r;
	DBL_EQUAL(a->Real, c_r - r_r, "Real @ Complex%");
	DBL_EQUAL(a->Imag, c_i - r_i, "Imag @ Complex%");

	std::mt19937 mt(762u);
	size_t mid = (mt.max() - mt.min() ) /2;
	double amp = 1500.0 / mid;

	for(int i = 0; i < 10; i++)
	{
		c_r = amp * (mt() - mid);
		c_i = amp * (mt() - mid);
		o_r = amp * (mt() - mid);
		o_i = amp * (mt() - mid);
		r_r = amp * (mt() - mid);
		r_i = amp * (mt() - mid);

		c.Real = c_r;
		c.Imag = c_i;
		o->Real = o_r;
		o->Imag = o_i;
		r.Real = r_r;
		r.Imag = r_i;

		a = c - d;
		DBL_EQUAL(a->Real, c_r - d, "Real @ dobule (rand)");
		DBL_EQUAL(a->Imag, c_i    , "Imag @ double (rand)");

		a = d - c;
		DBL_EQUAL(a->Real, -c_r + d, "Real @ dobule- (rand)");
		DBL_EQUAL(a->Imag, -c_i    , "Imag @ double- (rand)");

		a = c - o;
		DBL_EQUAL(a->Real, c_r - o_r, "Real @ Complex^ (rand)");
		DBL_EQUAL(a->Imag, c_i - o_i, "Imag @ Complex^ (rand)");

		a = c - r;
		DBL_EQUAL(a->Real, c_r - r_r, "Real @ Complex% (rand)");
		DBL_EQUAL(a->Imag, c_i - r_i, "Imag @ Complex% (rand)");
	}

}


void test_complex_mul()
{
	ENTER("COMPLEX MUL");

	double c_r = 1.0, c_i = 2.0;
	double r_r = 7.0, r_i = -5.0;
	double o_r = 3.0, o_i = 6.0;
	double d = 2.0;

	Complex^ c, ^a, ^o, r(r_r, r_i);
	c = gcnew Complex(c_r, c_i);
	o = gcnew Complex(o_r, o_i);

	std::complex<double> s_c(c_r, c_i), s_o(o_r, o_i), s_r(r_r, r_i);

	a = c * r_i;
	std::complex<double> ans = s_c * r_i;
	DBL_EQUAL(a->Real, ans.real(), "Real @ dobule ");
	DBL_EQUAL(a->Imag, ans.imag(), "Imag @ double ");

	a = r_i * c;
	DBL_EQUAL(a->Real, ans.real(), "Real @ dobule*");
	DBL_EQUAL(a->Imag, ans.imag(), "Imag @ double*");

	a = c * o;
	ans = s_c * s_o;
	DBL_EQUAL(a->Real, ans.real(), "Real @ Complex^ ");
	DBL_EQUAL(a->Imag, ans.imag(), "Imag @ Complex^ ");

	a = c * r;
	ans = s_c * s_r;
	DBL_EQUAL(a->Real, ans.real(), "Real @ Complex% ");
	DBL_EQUAL(a->Imag, ans.imag(), "Imag @ Complex% ");


	std::mt19937 mt(762u);
	size_t mid = (mt.max() - mt.min() ) /2;
	double amp = 1500.0 / mid;

	for(int i = 0; i < 10; i++)
	{
		c_r = amp * (mt() - mid);
		c_i = amp * (mt() - mid);
		o_r = amp * (mt() - mid);
		o_i = amp * (mt() - mid);
		r_r = amp * (mt() - mid);
		r_i = amp * (mt() - mid);

		c->Real = c_r; c->Imag = c_i;
		o->Real = o_r; o->Imag = o_i;
		r.Real = r_r;  r.Imag = r_i;
		s_c.real(c_r); s_c.imag(c_i);
		s_o.real(o_r); s_o.imag(o_i);
		s_r.real(r_r); s_r.imag(r_i);

		a = c * r_i;
		ans = s_c * r_i;
		DBL_EQUAL(a->Real, ans.real(), "Real @ dobule (rand)");
		DBL_EQUAL(a->Imag, ans.imag(), "Imag @ double (rand)");

		a = r_i * c;
		DBL_EQUAL(a->Real, ans.real(), "Real @ dobule* (rand)");
		DBL_EQUAL(a->Imag, ans.imag(), "Imag @ double* (rand)");

		a = c * o;
		ans = s_c * s_o;
		DBL_EQUAL(a->Real, ans.real(), "Real @ Complex^ (rand)");
		DBL_EQUAL(a->Imag, ans.imag(), "Imag @ Complex^ (rand)");

		a = c * r;
		ans = s_c * s_r;
		DBL_EQUAL(a->Real, ans.real(), "Real @ Complex% (rand)");
		DBL_EQUAL(a->Imag, ans.imag(), "Imag @ Complex% (rand)");
	}
}

void test_complex_ref_mul()
{
	ENTER("Complex Ref MUL");
	double c_r = 21.0, c_i = 22.0;
	double r_r = 67.0, r_i = -53.0;
	double o_r = 83.0, o_i = 64.0;
	double d = 82.0;

	Complex c(c_r,c_i), ^a, ^o, r(r_r, r_i);
	o = gcnew Complex(o_r, o_i);

	std::complex<double> s_c(c_r, c_i), s_o(o_r, o_i), s_r(r_r, r_i);

	a = c * r_i;
	std::complex<double> ans = s_c * r_i;
	DBL_EQUAL(a->Real, ans.real(), "Real @ dobule ");
	DBL_EQUAL(a->Imag, ans.imag(), "Imag @ double ");
	a = r_i * c;
	DBL_EQUAL(a->Real, ans.real(), "Real @ dobule ");
	DBL_EQUAL(a->Imag, ans.imag(), "Imag @ double ");

	a = c * o;
	ans = s_c * s_o;
	DBL_EQUAL(a->Real, ans.real(), "Real @ Complex^ ");
	DBL_EQUAL(a->Imag, ans.imag(), "Imag @ Complex^ ");

	a = c * r;
	ans = s_c * s_r;
	DBL_EQUAL(a->Real, ans.real(), "Real @ Complex% ");
	DBL_EQUAL(a->Imag, ans.imag(), "Imag @ Complex% ");


	std::mt19937 mt(762u);
	size_t mid = (mt.max() - mt.min() ) /2;
	double amp = 1500.0 / mid;

	for(int i = 0; i < 10; i++)
	{
		c_r = amp * (mt() - mid);
		c_i = amp * (mt() - mid);
		o_r = amp * (mt() - mid);
		o_i = amp * (mt() - mid);
		r_r = amp * (mt() - mid);
		r_i = amp * (mt() - mid);

		c.Real = c_r; c.Imag = c_i;
		o->Real = o_r; o->Imag = o_i;
		r.Real = r_r;  r.Imag = r_i;
		s_c.real(c_r); s_c.imag(c_i);
		s_o.real(o_r); s_o.imag(o_i);
		s_r.real(r_r); s_r.imag(r_i);

		a = c * r_i;
		ans = s_c * r_i;
		DBL_EQUAL(a->Real, ans.real(), "Real @ dobule (rand)");
		DBL_EQUAL(a->Imag, ans.imag(), "Imag @ double (rand)");

		a = r_i * c;
		DBL_EQUAL(a->Real, ans.real(), "Real @ dobule * (rand)");
		DBL_EQUAL(a->Imag, ans.imag(), "Imag @ double * (rand)");

		a = c * o;
		ans = s_c * s_o;
		DBL_EQUAL(a->Real, ans.real(), "Real @ Complex^ (rand)");
		DBL_EQUAL(a->Imag, ans.imag(), "Imag @ Complex^ (rand)");

		a = c * r;
		ans = s_c * s_r;
		DBL_EQUAL(a->Real, ans.real(), "Real @ Complex% (rand)");
		DBL_EQUAL(a->Imag, ans.imag(), "Imag @ Complex% (rand)");
	}
}


void test_complex_div()
{
	ENTER("COMPLEX DIV");

	double c_r = 1.0, c_i = 2.0;
	double r_r = 7.0, r_i = -5.0;
	double o_r = 3.0, o_i = 6.0;
	double d = 2.0;

	Complex^ c, ^a, ^o, r(r_r, r_i);
	c = gcnew Complex(c_r, c_i);
	o = gcnew Complex(o_r, o_i);

	std::complex<double> s_c(c_r, c_i), s_o(o_r, o_i), s_r(r_r, r_i);

	a = c / r_i;
	std::complex<double> ans = s_c / r_i;
	DBL_EQUAL(a->Real, ans.real(), "Real @ dobule ");
	DBL_EQUAL(a->Imag, ans.imag(), "Imag @ double ");

	a = o_i / c;
    ans = o_i / s_c;
	DBL_EQUAL(a->Real, ans.real(), "Real @ dobule /");
	DBL_EQUAL(a->Imag, ans.imag(), "Imag @ double /");

	a = c / o;
	ans = s_c / s_o;
	DBL_EQUAL(a->Real, ans.real(), "Real @ Complex^ ");
	DBL_EQUAL(a->Imag, ans.imag(), "Imag @ Complex^ ");

	a = c / r;
	ans = s_c / s_r;
	DBL_EQUAL(a->Real, ans.real(), "Real @ Complex% ");
	DBL_EQUAL(a->Imag, ans.imag(), "Imag @ Complex% ");


	std::mt19937 mt(762u);
	size_t mid = (mt.max() - mt.min() ) /2;
	double amp = 1500.0 / mid;

	for(int i = 0; i < 10; i++)
	{
		c_r = amp * (mt() - mid);
		c_i = amp * (mt() - mid);
		o_r = amp * (mt() - mid);
		o_i = amp * (mt() - mid);
		r_r = amp * (mt() - mid);
		r_i = amp * (mt() - mid);

		c->Real = c_r; c->Imag = c_i;
		o->Real = o_r; o->Imag = o_i;
		r.Real = r_r;  r.Imag = r_i;
		s_c.real(c_r); s_c.imag(c_i);
		s_o.real(o_r); s_o.imag(o_i);
		s_r.real(r_r); s_r.imag(r_i);

		a = c / r_i;
		ans = s_c / r_i;
		DBL_EQUAL(a->Real, ans.real(), "Real @ dobule (rand)");
		DBL_EQUAL(a->Imag, ans.imag(), "Imag @ double (rand)");

		a = o_i / c;
		ans = o_i / s_c;
		DBL_EQUAL(a->Real, ans.real(), "Real @ dobule (rand)");
		DBL_EQUAL(a->Imag, ans.imag(), "Imag @ double (rand)");

		a = c / o;
		ans = s_c / s_o;
		DBL_EQUAL(a->Real, ans.real(), "Real @ Complex^ (rand)");
		DBL_EQUAL(a->Imag, ans.imag(), "Imag @ Complex^ (rand)");

		a = c / r;
		ans = s_c / s_r;
		DBL_EQUAL(a->Real, ans.real(), "Real @ Complex% (rand)");
		DBL_EQUAL(a->Imag, ans.imag(), "Imag @ Complex% (rand)");
	}
}

void test_complex_ref_div()
{
	ENTER("Complex Ref DIV");
	double c_r = 21.0, c_i = 22.0;
	double r_r = 67.0, r_i = -53.0;
	double o_r = 83.0, o_i = 64.0;
	double d = 82.0;

	Complex c(c_r,c_i), ^a, ^o, r(r_r, r_i);
	o = gcnew Complex(o_r, o_i);

	std::complex<double> s_c(c_r, c_i), s_o(o_r, o_i), s_r(r_r, r_i);

	a = c / r_i;
	std::complex<double> ans = s_c / r_i;
	DBL_EQUAL(a->Real, ans.real(), "Real @ dobule ");
	DBL_EQUAL(a->Imag, ans.imag(), "Imag @ double ");

	a = o_i / c;
    ans = o_i / s_c;
	DBL_EQUAL(a->Real, ans.real(), "Real @ dobule ");
	DBL_EQUAL(a->Imag, ans.imag(), "Imag @ double ");

	a = c / o;
	ans = s_c / s_o;
	DBL_EQUAL(a->Real, ans.real(), "Real @ Complex^ ");
	DBL_EQUAL(a->Imag, ans.imag(), "Imag @ Complex^ ");

	a = c / r;
	ans = s_c / s_r;
	DBL_EQUAL(a->Real, ans.real(), "Real @ Complex% ");
	DBL_EQUAL(a->Imag, ans.imag(), "Imag @ Complex% ");


	std::mt19937 mt(762u);
	size_t mid = (mt.max() - mt.min() ) /2;
	double amp = 1500.0 / mid;

	for(int i = 0; i < 10; i++)
	{
		c_r = amp * (mt() - mid);
		c_i = amp * (mt() - mid);
		o_r = amp * (mt() - mid);
		o_i = amp * (mt() - mid);
		r_r = amp * (mt() - mid);
		r_i = amp * (mt() - mid);

		c.Real = c_r; c.Imag = c_i;
		o->Real = o_r; o->Imag = o_i;
		r.Real = r_r;  r.Imag = r_i;
		s_c.real(c_r); s_c.imag(c_i);
		s_o.real(o_r); s_o.imag(o_i);
		s_r.real(r_r); s_r.imag(r_i);

		a = c / r_i;
		ans = s_c / r_i;
		DBL_EQUAL(a->Real, ans.real(), "Real @ dobule (rand)");
		DBL_EQUAL(a->Imag, ans.imag(), "Imag @ double (rand)");

		a = o_i / c;
		ans = o_i / s_c;
		DBL_EQUAL(a->Real, ans.real(), "Real @ dobule /(rand)");
		DBL_EQUAL(a->Imag, ans.imag(), "Imag @ double /(rand)");

		a = c / o;
		ans = s_c / s_o;
		DBL_EQUAL(a->Real, ans.real(), "Real @ Complex^ (rand)");
		DBL_EQUAL(a->Imag, ans.imag(), "Imag @ Complex^ (rand)");

		a = c / r;
		ans = s_c / s_r;
		DBL_EQUAL(a->Real, ans.real(), "Real @ Complex% (rand)");
		DBL_EQUAL(a->Imag, ans.imag(), "Imag @ Complex% (rand)");
	}
}




void test_assign()
{
	ENTER(L"Assign");
	array<double>^ arr = {1.0, 2.0, 3.0, 4.0};

	ComplexArray ca(3, true);
	for(int i = 0; i < 3; ++i)
	{
		IN_DELTA(ca[i]->Real, 0.0, 0.0001, "Init Real");
		IN_DELTA(ca[i]->Imag, 0.0, 0.0001, "Init Imag");
	}
	ca.real_assign(arr);
	for(int i = 0; i < 3; ++i)
	{
		IN_DELTA(ca[i]->Real, arr[i], 0.0001, "Assigned Real");
		IN_DELTA(ca[i]->Imag, 0.0, 0.0001, "original Imag");
	}
	array<double>^ rev =  {4.0, 3.0};
	ca.imag_assign(rev);
	//  ca->imag_assign(Enumerable::Take(Enumerable::Reverse(arr),2));
	IN_DELTA(ca[0]->Real, 1.0, 0.0001, "Assigned Real0");
	IN_DELTA(ca[0]->Imag, 4.0, 0.0001, "Assigned Imag0");
	IN_DELTA(ca[1]->Real, 2.0, 0.0001, "Assigned Real1");
	IN_DELTA(ca[1]->Imag, 3.0, 0.0001, "Assigned Imag1");
	IN_DELTA(ca[2]->Real, 3.0, 0.0001, "Assigned Real2");
	IN_DELTA(ca[2]->Imag, 0.0, 0.0001, "Not Assigned Imag2");

}

void test_operator_plus_equal_complex_array()
{
	ENTER(L"OP += ComplexArray");
	array<double>^ arr = {0.0, 1.0, 2.0, 3.0};
	array<double>^ opr = {8.0, 6.0, 4.0, 2.0};
	array<double>^ ans = {8.0, 7.0, 6.0, 5.0};
	array<double>^ differ = {9.9, 8.8};

	ComplexArray ca(arr);
	ComplexArray o(opr);
	ca += o;

	IN_DELTA(ca[0]->Real, ans[0], 0.001, "");
	IN_DELTA(ca[0]->Imag, ans[1], 0.001, "");
	IN_DELTA(ca[1]->Real, ans[2], 0.001, "");
	IN_DELTA(ca[1]->Imag, ans[3], 0.001, "");

	try{
		ComplexArray d(differ);
		ca += d;
		Console::WriteLine("Error: No Exception Thrown");
	}
	catch(Exception^ e)
	{
		Console::Write(".");
	}

}


void test_operator_plus_complex_array()
{
	ENTER(L"OP += ComplexArray");
	array<double>^ arr = {0.0, 1.0, 2.0, 3.0};
	array<double>^ opr = {8.0, 6.0, 4.0, 2.0};
	array<double>^ ans = {8.0, 7.0, 6.0, 5.0};
	array<double>^ differ = {9.9, 8.8};

	ComplexArray x(arr);
	ComplexArray y(opr);

	ComplexArray^ ca = x + y;

	IN_DELTA(ca[0]->Real, ans[0], 0.001, "res 1");
	IN_DELTA(ca[0]->Imag, ans[1], 0.001, "res 2");
	IN_DELTA(ca[1]->Real, ans[2], 0.001, "res 3");
	IN_DELTA(ca[1]->Imag, ans[3], 0.001, "res 4");

	IN_DELTA(x[0]->Real, arr[0], 0.001, "x1");
	IN_DELTA(x[0]->Imag, arr[1], 0.001, "x2");
	IN_DELTA(x[1]->Real, arr[2], 0.001, "x3");
	IN_DELTA(x[1]->Imag, arr[3], 0.001, "x4");

	IN_DELTA(y[0]->Real, opr[0], 0.001, "y1");
	IN_DELTA(y[0]->Imag, opr[1], 0.001, "y2");
	IN_DELTA(y[1]->Real, opr[2], 0.001, "y3");
	IN_DELTA(y[1]->Imag, opr[3], 0.001, "y4");

	try{
		ComplexArray d(differ);
		ca = x + d;
		Console::WriteLine("Error: No Exception Thrown");
	}
	catch(Exception^ e)
	{
		Console::Write(".");
	}

}

void test_fft_impulse()
{
	ENTER("FFT_IMPULSE");

	int n = 8;

	ComplexArray ca(n,true);
	ca[0]->Real = 1.0;

	ComplexArray^ sp = ca.fft();

	for(int i = 0; i < n; ++i)
	{
		IN_DELTA(sp[i]->Real, 1.0, 0.0001, "Real");
		IN_DELTA(sp[i]->Imag, 0.0, 0.0001, "Imag");
	}

}

void test_ifft_impulse()
{
	ENTER("IFFT Implse");

	int n = 8;
	array<double>^ arr = gcnew array<double>(n);
	for(int i = 0; i < n; ++i)
	{
		arr[i] = 1.0;
	}
	ComplexArray^ ca = ComplexArray::real(arr);
	ComplexArray^ res = nullptr;
	try{
		res = ca->ifft();
		IN_DELTA(res[0]->Real,   n, 0.00001, "Impulse");
		IN_DELTA(res[0]->Imag, 0.0, 0.00001, "Imag");
		for(int i = 1; i < n; i++)
		{
			IN_DELTA(res[i]->Real, 0.0, 0.00001, "Real");
			IN_DELTA(res[i]->Imag, 0.0, 0.00001, "Imag");
		}
	}
	finally{
		delete ca;
		delete res;
	}
}


int main(array<System::String ^> ^args)
{

	test_basic();
	test_real_construction();
	test_imag_construction();
	test_real_enumerator();
	test_imag_enumerator();
	test_complex();
	test_complex_add();
	test_complex_sub();
	test_complex_mul();
	test_complex_div();
	test_complex_ref_add();
	test_complex_ref_sub();
	test_complex_ref_mul();
	test_complex_ref_div();
	test_operator_plus_equal_double();
	test_operator_plus_double();
	test_operator_plus_equal_complex();
	test_operator_plus_complex();
	test_assign();
	test_operator_plus_equal_complex_array();
	test_operator_plus_complex_array();

	test_fft_impulse();
	test_ifft_impulse();
	Console::WriteLine();
	Console::WriteLine("Press Any Key.");
	Console::ReadLine();

	return 0;
}
