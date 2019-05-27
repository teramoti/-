//------------------------//------------------------
// Contents(�������e) Player.cpp�̓��e������
//------------------------//------------------------
// user(�쐬��) Keishi Teramoto
// Created date(�쐬��) 2018 / 09 / 23
// last updated (�ŏI�X�V��) 2018 / 5 / 22
//------------------------//------------------------

#include <d3d11.h>
#include <SimpleMath.h>
#include <KeyBoard.h>
#include "../../GameSystem/InputManager.h"

#include "TestPlayer.h"



TestPlayer::TestPlayer() : m_angle(0.0f), m_rotation(DirectX::SimpleMath::Quaternion::Identity), m_velocity(DirectX::SimpleMath::Vector3::Zero),
m_pos(DirectX::SimpleMath::Vector3(0.0f, 0.0f, -0.0f)), m_acceleration(0.0f), m_startFlag(false)
{
}

TestPlayer::~TestPlayer()
{
}

void TestPlayer::Initilize(Shadow* shadow)
{
	m_translation = DirectX::SimpleMath::Vector3(0,0,0);
		
	m_directX11.Get().GetEffect()->SetDirectory(L"Resources\\Model");
	m_box.Initialize();
	m_box.SetTrans(m_translation);
	m_box.SetSize(DirectX::SimpleMath::Vector3(1, 1, 1));

	m_sphere.Initialize();
	m_sphere.Center = DirectX::SimpleMath::Vector3(m_translation);
	m_sphere.Radius = 1.0f;
	CreateResource();
}

void TestPlayer::CreateResource()
{
	m_model = DirectX::Model::CreateFromCMO(m_directX11.GetDevice().Get(), L"Resources\\Model\\Player.cmo", *m_directX11.Get().GetEffect());
}

void TestPlayer::Update(bool flag)
{


	m_startFlag = flag;

	MyLib::Object3D::Update();
	m_box.Update();
	m_box.SetTrans(m_translation);

	m_sphere.SetTrans(m_translation);
	m_sphere.Update();

	//�v���C���[�̈ړ�
	PlayerMove();

}

void TestPlayer::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	m_model->Draw(m_directX11.GetContext().Get(), *m_directX11.Get().GetStates(), m_world, view, proj);
}

void TestPlayer::Lost()
{
}

void TestPlayer::PlayerMove()
{
	bool keyFlag = false;

	vec = DirectX::SimpleMath::Vector3::Zero;

	//�v���C���[�̈ړ�
	//��ړ�
	if (m_startFlag == true)
	{
		if (System::InputManager::GetInstance().GetKeyboardState().Up)
		{
			vec.z = 0.1f/* * m_boost*/;

			m_acceleration += 0.2f;
		}
		else
		{
			vec.z = 0.1f/* * m_boost*/;

			m_acceleration *= 0.98f;
		}

		//���ړ�
		if (System::InputManager::GetInstance().GetKeyboardState().Down)
		{
			m_acceleration *= 0.98f;

			keyFlag = true;
		}


		//�E�ړ�
		if (System::InputManager::GetInstance().GetKeyboardState().Left)
		{
			m_angle += DirectX::XMConvertToRadians(2.0f);

			m_rotation = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f), DirectX::XMConvertToRadians(1.5f));
			m_velocity = DirectX::SimpleMath::Vector3::Transform(m_velocity, m_rotation);
			SetRotation(m_rotation);

		}

		//���ړ�
		if (System::InputManager::GetInstance().GetKeyboardState().Right)
		{
			m_angle -= DirectX::XMConvertToRadians(2.0f);

			m_rotation = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f), DirectX::XMConvertToRadians(-1.5f));
			m_velocity = DirectX::SimpleMath::Vector3::Transform(m_velocity, m_rotation);

			SetRotation(DirectX::SimpleMath::Quaternion(m_rotation.w, m_rotation.x-100.0f, m_rotation.y - 0.3f, m_rotation.z));
		}
	}

	//�����xMAX
	if (m_acceleration > MAX_ACCELERATION)
	{
		m_acceleration = MAX_ACCELERATION;
	}

	//�����xMIN
	if (m_acceleration < MIN_ACCELERATION)
	{
		m_acceleration = MIN_ACCELERATION;
	}


	//�p�x�̐ݒ�

	m_rotation = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f), m_angle);
	vec = DirectX::SimpleMath::Vector3::Transform(vec, m_rotation);
	m_velocity = vec * (m_acceleration);


	// ���x�ɏd�͉����x�𑫂�
	m_velocity.y -= GRAVITY * (1.0f / 60.0f);

	// �ʒu�ɑ��x�𑫂�
	m_pos += m_velocity;

	// �n�ʂɂ߂荞�܂Ȃ����߂̏���������
	if (m_pos.y < 0.0f)
	{
		m_pos.y = 0.0f;
	}
	m_translation = m_pos;

	SetTranslation(m_translation);//�ʒu�̐ݒ�
	SetAngle(m_angle);//�p�x�̐ݒ�
	SetRotation(m_rotation);//��]�̐ݒ�

}
