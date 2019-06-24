//------------------------//------------------------
// Contents(�������e) Math.cpp�̓��e������
//------------------------//------------------------
// user(�쐬��) Keishi Teramoto
// Created date(�쐬��) 2018 / 07 / 07
// last updated (�ŏI�X�V��) 2018 / 07 / 07
//------------------------//------------------------
// �w�b�_�t�@�C���̓ǂݍ��� ================================================

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Math.h"

using namespace std;
using namespace Teramoto;

// ��
const float Teramoto::Math::PI = 3.14159274f;

/// <summary>
/// ��Βl��Ԃ�
/// </summary>
/// <param name="num">���l</param>
/// <returns>��Βl</returns>
template<typename T>
T Teramoto::Math::Abs(T num)
{
	if (num < 0)
	{
		num *= -1;
	}
	return num;
}

/// <summary>
/// 2�_�̋��������߂�
/// <summary>
/// <param name="p1">�_1</param>
/// <param name="p2">�_2</param>
/// <returns>����</returns>
template<typename T>
inline T Math::Difference(T p1, T p2)
{
	auto length = p1 - p2;
	return Abs<T>(length);
}

/// <summary>
/// ��������^�[�Q�b�g�ւ̕���(�p�x)�����߂�
/// </summary>
/// <param name="myPos1">2D(�����̍��WX)or3D(�����̍��WZ)</param>
/// <param name="myPos2">2D(�����̍��WY)or3D(�����̍��WX)</param>
/// <param name="targetPos1">2D(�Ώۂ̍��WX)or3D(�Ώۂ̍��WZ)</param>
/// <param name="targetPos2">2D(�Ώۂ̍��WY)or3D(�Ώۂ̍��WX)</param>
/// <returns>�Ώە��ւ̊p�x</returns>
float Teramoto::Math::TargetAngle(float myPos1, float myPos2, float targetPos1, float targetPos2)
{
	float dPos1;
	float dPos2;
	float angle;

	dPos1 = myPos1 - targetPos1;
	dPos2 = myPos2 - targetPos2;

	angle = float(atan2(dPos2, dPos1));

	return angle;	
}
	

template<typename T>
bool Teramoto::Math::Clamp(T value, T num1, T num2)
{
	if (num1 < num2)
	{
		if (value > num2) return false;
		if (value < num1) return false;

		return true;
	}

	if (num1 > num2)
	{
		if (value < num2) return false;
		if (value > num1) return false;

		return true;
	}

	return true;
}
//bool MyLibrary::Math::Clamp(T value, T lo, T hi)
//{
//	if(value < hi)  return false;
//	if(value > lo)	return false;
//
//	return true;
//}

/// <summary>
/// �����̎擾(int�^)
/// </summary>
/// <param name="min">�ŏ��l</param>
/// <param name="max">�ő�l</param>
/// <returns>min����max�̊Ԃ̒l</returns>
int Teramoto::Math::GetRand(int min, int max)
{
	int random;

	srand((unsigned)time(NULL));
	random = rand() % (max - min + 1) + min;

	return random;
}

/// <summary>
/// �f�O���[�����W�A���ɕϊ�
/// </summary>
/// <param name="deg">�f�O���[�p</param>
/// <returns>���W�A���p</returns>
float Teramoto::Math::ToRad(float deg)
{
	return deg * (PI / 180.f);
}

/// <summary>
/// ���W�A�����f�O���[�ɕϊ�
/// </summary>
/// <param name="rad">���W�A���p</param>
/// <returns>�f�O���[�p</returns>
float Teramoto::Math::ToDeg(float rad)
{
	return rad * (180.f * PI);
}
