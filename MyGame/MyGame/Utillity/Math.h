//------------------------//------------------------
// Contents(�������e) math.h�̓��e������
//------------------------//------------------------
// user(�쐬��) Keishi Teramoto
// Created date(�쐬��) 2018 / 07 / 06
// last updated (�ŏI�X�V��) 2018 / 07 / 06
//------------------------//------------------------
// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include <math.h>


/// <summary>
//!
//! @brief Math�N���X
//!
/// </summary>
namespace MyLibrary
{
	class Math
	{
	private:
		// �~����
		static const float PI;

	public:
		// ��Βl�����߂�
		template<typename T>
		static T Abs(T num);

		// ��̓_�̍��������߂�
		template<typename T>
		static T Difference(T p1, T p2);

		// ��������^�[�Q�b�g�ւ̕���(�p�x)�����߂�
		static float TargetAngle(float myPos1, float myPos2, float targetPos1, float targetPos2);

		// �N�����v�֐�
		template<typename T>
		static bool Clamp(T value, T num1, T num2);


		// ����
		static int GetRand(int min, int max);

		// �f�O���[�����W�A���ɕϊ�
		static float ToRad(float deg);

		// ���W�A�����f�O���[�ɕϊ�
		static float ToDeg(float rad);
	
	};

}

