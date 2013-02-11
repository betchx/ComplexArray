// stdafx.cpp : 標準インクルード ComplexArray.pch のみを
// 含むソース ファイルは、プリコンパイル済みヘッダーになります。
// stdafx.obj にはプリコンパイル済み型情報が含まれます。

#include "stdafx.h"

namespace std{
	// VC hasn't int version of to_string
	string to_string(int val){return to_string((long long)val);}
}
