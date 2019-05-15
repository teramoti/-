//--------------------------------------------------------------------------------------
// File: Ball.h
//
//
// Date: 2018. 7.24
// Author: Daisuke Shimizu
//--------------------------------------------------------------------------------------

// �C���N���[�h
#include "pch.h"
#include "Ball.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
/// <summary>
/// �R���X�g���N�^
/// </summary>
Ball::Ball()
	:Obj3D(), m_direction(0.0f),m_move(MOVE::STOP)
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime"></param>
/// <returns></returns>
bool Ball::Update(float elapsedTime)
{
	// �����x
	Vector3 a;

	switch (m_move)
	{
	case MOVE::FORWARD:
		a.z = -0.01f;
		break;
	case MOVE::BACK:
		a.z = 0.01f;
		break;
	case MOVE::TURN_LEFT:
		m_direction += XMConvertToRadians(1);
		break;
	case MOVE::TURN_RIGHT:
		m_direction -= XMConvertToRadians(1);
		break;
	}

	// �~�߂�
	m_move = MOVE::STOP;

	// �����x��Ball�̌����ɉ�]������
	Matrix rotY = Matrix::CreateRotationY(m_direction);
	a = Vector3::Transform(a, rotY);
	// ���x�ɉ����x�𑫂�
	m_vel += a;
	// �ʒu�ɑ��x�𑫂�
	m_position += m_vel;

	// �ړ������Ƀ{�[������]������
	Vector3 axis(1, 0, 0);
	rotY = Matrix::CreateRotationY(atan2f(m_vel.x, m_vel.z));
	axis = Vector3::Transform(axis, rotY);

	// Ball�̔��a��1�Ȃ̂ňړ��ʂ���]�ʂɂȂ�
	m_rotation *= Quaternion::CreateFromAxisAngle(axis, m_vel.Length());
	// ���C�ɂ�茸��������(�K��)
	m_vel *= 0.99f;

	// ���[���h�s����쐬
	m_world = Matrix::CreateFromQuaternion(m_rotation)
		* Matrix::CreateTranslation(m_position);

	return true;
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="move"></param>
void Ball::Move(MOVE move)
{
	m_move = move;
}

/// <summary>
/// �������擾����֐�
/// </summary>
/// <returns></returns>
float Ball::GetDirection()
{
	return m_direction;
}

/// <summary>
/// ���f����ݒ肷��֐�
/// </summary>
/// <param name="model"></param>
void Ball::SetModel(DirectX::Model * model)
{
	m_model = model;
	// Effect���X�V����
	m_model->UpdateEffects([&](IEffect* effect)
	{
		auto lights = dynamic_cast<IEffectLights*>(effect);
		if (lights)
		{
			// �s�N�Z���P�ʂŃ��C�g�̌v�Z������
			lights->SetPerPixelLighting(true);
		}
	});
}
