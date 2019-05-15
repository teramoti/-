#pragma once
#include "../../GameSystem/TpsCamera.h"
#include "../../GameSystem/Object.h"
#include "../../Collison/MyCollisionNode.h"

class TestPlayer : public MyLib::Object3D
{

public:
	TestPlayer();//�R���X�g���N�^
	~TestPlayer();//�f�X�g���N�^
public:

	void Initilize();//����������
	void Update(bool flag);//�X�V����
	void Render();//�`�揈��()
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

	const float GRAVITY;//�d��

	BoxNode& GetBox()
	{
		return m_box;
	}

private:

	//Player�̏��
	DirectX::SimpleMath::Vector3 m_pos;//�|�W�V����

	DirectX::SimpleMath::Quaternion m_rotation;//��]

	DirectX::SimpleMath::Vector3 m_velocity;//���x
											
	//�����x
	float m_acceleration;

	const float MAX_ACCELERATION;//�ō����x
	const float MIN_ACCELERATION;//�Œᑬ�x2

	float m_angle = 0.0f;	//�p�x



	bool m_startFlag;//�n�܂������̃t���O�Ǘ�
	DirectX::SimpleMath::Vector3 vec;//���x�p�ϐ�

	BoxNode m_box;//�{�b�N�X��Node

	SphereNode m_sphere;//Sphere��Node

};

