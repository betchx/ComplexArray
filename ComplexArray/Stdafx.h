// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。

#pragma once

#define _SECURE_SCL 0
#define _SCL_SECURE_NO_WARNINGS 1

#include <complex>
#include <fftw3.h>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

namespace std{
	// VC hasn't int version of to_string
	string to_string(int val);//{return to_string((long long)val);}
}
