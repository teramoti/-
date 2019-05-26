#pragma once
#include <Model.h>
#include <CommonStates.h>

#include <Effects.h>
#include "TpsCamera.h"

#include "../../GameSystem/Object.h"
#include "../../Collison/MyCollisionNode.h"
#include "Shadow.h"
class TestPlayer : public MyLib::Object3D
{

public:
	TestPlayer();//�R���X�g���N�^
	~TestPlayer();//�f�X�g���N�^
public:

	void Initilize(Shadow* shadow);//����������
	void CreateResource();
	void Update(bool flag);//�X�V����
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);//�`�揈��()
	void Lost();//�폜���鏈��
	void PlayerMove();	//�v���C���[���ړ�����֐�

	//velcity��Get�֐�
	DirectX::SimpleMath::Vector3 GetVel()
	{
		return m_velocity;
	}
	//velcity�̃Z�b�g�p�֐�
	void SetVel(DirectX::SimpleMath::Vector3 vel)
	{
		m_velocity = vel;
	}


	BoxNode& GetBox()
	{
		return m_box;
	}

private:

	//
	Shadow* m_shadow;


	//Player�̏��
	DirectX::SimpleMath::Vector3 m_pos;//�|�W�V����

	DirectX::SimpleMath::Quaternion m_rotation;//��]

	DirectX::SimpleMath::Vector3 m_velocity;//���x
											
	//�����x
	float m_acceleration;

	const float GRAVITY=0.98f;//�d��
	const float MAX_ACCELERATION=45.0f;//�ō����x
	const float MIN_ACCELERATION= 0.0f; //�Œᑬ�x

	float m_angle = 0.0f;	//�p�x



	bool m_startFlag;//�n�܂������̃t���O�Ǘ�
	
	std::unique_ptr<DirectX::Model> m_model;
	DirectX::SimpleMath::Vector3 vec;//���x�p�ϐ�

	std::unique_ptr<DirectX::CommonStates> m_States;
	std::unique_ptr<DirectX::EffectFactory> m_Factory;

	BoxNode m_box;//�{�b�N�X��Node

	SphereNode m_sphere;//Sphere��Node

};

