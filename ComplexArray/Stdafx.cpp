// stdafx.cpp : �W���C���N���[�h ComplexArray.pch �݂̂�
// �܂ރ\�[�X �t�@�C���́A�v���R���p�C���ς݃w�b�_�[�ɂȂ�܂��B
// stdafx.obj �ɂ̓v���R���p�C���ς݌^��񂪊܂܂�܂��B

#include "stdafx.h"

namespace std{
	// VC hasn't int version of to_string
	string to_string(int val){return to_string((long long)val);}
}
