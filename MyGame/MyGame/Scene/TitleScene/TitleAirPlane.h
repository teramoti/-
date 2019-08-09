#pragma once


#include <Model.h>
#include <CommonStates.h>

#include <Effects.h>
#include "../../Scene/GameScene/TpsCamera.h"
#include "../../Collison/Collision.h"
#include "../../GameSystem/Object.h"
#include "../../Utillity/DirectX11.h"
#include "../GameScene/Shadow.h"

class TitleAirPlane : public Teramoto::Object3D
{

public:
	//�R���X�g���N�^
	TitleAirPlane();
	//�f�X�g���N�^
	~TitleAirPlane();
public:

	//����������
	void Initilize();
	void CreateResource();
	//�X�V����
	void Update();
	//�`�揈��()
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	//�폜���鏈��
	void Lost();
	//�v���C���[���ړ�����֐�
	void MyAirPlaneMove();

	//velcity��Get�֐�
	DirectX::SimpleMath::Vector3 GetVelotity()
	{
		return m_velocity;
	}
	//velcity�̃Z�b�g�p�֐�
	void SetVel(DirectX::SimpleMath::Vector3 vel)
	{
		m_velocity = vel;
	}



private:

	//�e�̕`��
	Shadow* m_shadow;

	//�|�W�V����
	DirectX::SimpleMath::Vector3 m_pos;

	//��]
	DirectX::SimpleMath::Quaternion m_rotation;

	//���x
	DirectX::SimpleMath::Vector3 m_velocity;

	//�����x
	float m_acceleration;

	//�d��
	const float GRAVITY = 0.98f;
	//�ō����x
	const float MAX_ACCELERATION = 80.0f;
	//�Œᑬ�x
	const float MIN_ACCELERATION = 0.0f;

public:
	//�p�x
	float m_angle;

	//���f���̒�`
	std::unique_ptr<DirectX::Model> m_model;
	//���x�p�ϐ�
	DirectX::SimpleMath::Vector3 vec;

	DirectX11& m_directX = DirectX11::Get();
};

