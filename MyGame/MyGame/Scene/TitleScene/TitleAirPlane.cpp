#include <d3d11.h>
#include <SimpleMath.h>
#include <KeyBoard.h>

#include "../../GameSystem/InputManager.h"

#include "TitleAirPlane.h"

TitleAirPlane::TitleAirPlane() : m_angle(0.0f), m_rotation(DirectX::SimpleMath::Quaternion::Identity),
m_velocity(DirectX::SimpleMath::Vector3::Zero),
m_pos(DirectX::SimpleMath::Vector3(0.0f, 0.0f, -0.0f)),
m_acceleration(0.0f)
{

}

TitleAirPlane::~TitleAirPlane()
{
}

void TitleAirPlane::Initilize()
{
	m_shadow = new Shadow();
	m_translation = DirectX::SimpleMath::Vector3(0, 0, 0);

	m_shadow->Initialize();

	m_directX11.Get().GetEffect()->SetDirectory(L"Resources\\Model");
	CreateResource();

}

void TitleAirPlane::CreateResource()
{
	m_model = DirectX::Model::CreateFromCMO(m_directX11.GetDevice().Get(), L"Resources\\Model\\Player.cmo", *m_directX11.Get().GetEffect());

}

void TitleAirPlane::Update()
{
	Teramoto::Object3D::Update();

	//�v���C���[�̈ړ�
	MyAirPlaneMove();

}

void TitleAirPlane::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	m_model->Draw(m_directX11.GetContext().Get(), *m_directX11.Get().GetStates(), m_world, view, proj);
	m_shadow->Render(view, proj, this, 0.3f);
}

void TitleAirPlane::Lost()
{
}

void TitleAirPlane::MyAirPlaneMove()
{
	bool keyFlag = false;

	vec.z = 0.1f;

	m_acceleration += 20.0f;

	//�����xMAX
	if (m_acceleration > MAX_ACCELERATION)
	{
		m_acceleration = MAX_ACCELERATION;
	}

	//�p�x�̐ݒ�
	m_rotation = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f), m_angle);
	vec = DirectX::SimpleMath::Vector3::Transform(vec, m_rotation);
	m_velocity = vec * (m_acceleration);


	// ���x�ɏd�͉����x�𑫂�
	m_velocity.y -= GRAVITY * (1.0f / 30.0f);

	// �ʒu�ɑ��x�𑫂�
	m_pos += m_velocity;

	// �n�ʂɂ߂荞�܂Ȃ����߂̏���������
	if (m_pos.y < 0.0f)
	{
		m_pos.y = 0.0f;
	}
	m_translation = m_pos;

	//�ʒu�̐ݒ�
	SetTranslation(m_translation);
	//�p�x�̐ݒ�
	SetAngle(m_angle);
	//��]�̐ݒ�
	SetRotation(m_rotation);

}
