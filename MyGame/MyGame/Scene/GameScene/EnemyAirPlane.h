#pragma once
#ifndef ENEMY_AIR_PLANE
#define ENEMY_AIR_PLANE
#include "MyNeuralNetwork.h"
#include "../../../StepTimer.h"
#include <Model.h>
#include <CommonStates.h>

#include <Effects.h>
#include "TpsCamera.h"

#include "../../GameSystem/Object.h"
#include "../../Collison/MyCollisionNode.h"

class EnemyAirPlane : Teramoto::Object3D
{
public:

	EnemyAirPlane();
	~EnemyAirPlane();

public:
	//����������
	void Initilize();


	//�X�V����
	void Update(DX::StepTimer& timer);
	//�`�揈��()
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	//�폜���鏈��
	void Lost();

	//���\�[�X�̐���
	void CreateResources();

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

	// Create neural network object
	NeuralNetwork	m_theAngleBrain;

	// Create neural network object
	NeuralNetwork	m_theSpeedBrain;


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
	const float MAX_ACCELERATION = 45.0f;
	//�Œᑬ�x
	const float MIN_ACCELERATION = 0.0f;

public:
	//�p�x
	float m_angle;
	//�n�܂������̃t���O�Ǘ�
	bool m_startFlag;

	//���f���̒�`
	std::unique_ptr<DirectX::Model> m_model;
	//���x�p�ϐ�
	DirectX::SimpleMath::Vector3 vec;


	//�{�b�N�X��Node
	BoxNode m_box;
};

#endif // !ENEMY_AIR_PLANE
