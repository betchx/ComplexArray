// stdafx.h : �W���̃V�X�e�� �C���N���[�h �t�@�C���̃C���N���[�h �t�@�C���A�܂���
// �Q�Ɖ񐔂������A�����܂�ύX����Ȃ��A�v���W�F�N�g��p�̃C���N���[�h �t�@�C��
// ���L�q���܂��B

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
