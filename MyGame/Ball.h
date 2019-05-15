//--------------------------------------------------------------------------------------
// File: Ball.h
//
//
// Date: 2018. 7.24
// Author: Daisuke Shimizu
//--------------------------------------------------------------------------------------

// ���d�C���N���[�h
#pragma once

// �C���N���[�h
//#include "Obj3D.h"

// Ball�N���X
class Ball : public Obj3D
{
public:
	enum class MOVE
	{
		STOP,
		FORWARD,
		BACK,
		TURN_LEFT,
		TURN_RIGHT,
	};

private:
	// ���x
	DirectX::SimpleMath::Vector3 m_vel;
	// ����
	float m_direction;

	// �ړ��X�e�[�g
	MOVE m_move;
public:
	// �R���X�g���N�^
	Ball();

	// �X�V�֐�
	bool Update(float elapsedTime) override;

	// �ړ��֐�
	void Move(MOVE move);

	// �������擾����֐�
	float GetDirection();

	// ���f����ݒ肷��֐�
	void SetModel(DirectX::Model* model);
};