#pragma once
#include "../../GameSystem/TpsCamera.h"
#include "../../GameSystem/Object.h"
#include "../../Collison/MyCollisionNode.h"

class TitlePlayer : public MyLib::Object3D
{

public:
	TitlePlayer();//�R���X�g���N�^
	~TitlePlayer();//�f�X�g���N�^
public:

	void Initilize();//����������
	void Update(bool flag);//�X�V����
	void Render();//�`�揈��()
	void Lost();//�폜���鏈��
	//�v���C���[���ړ�����֐�
	void PlayerMove();

	DirectX::SimpleMath::Vector3 GetVel()
	{
		return m_velocity;
	}

	void HitPlayer(bool Flag);

	void HitPlayer2(bool Flag);

	void SetVel(DirectX::SimpleMath::Vector3 vel)
	{
		m_velocity = vel;
	}

	bool GetEngine()
	{
		return m_engine;
	}
	const float GRAVITY;

	BoxNode& GetBox()
	{
		return m_box;
	}
private:


	//�����X�^�[01�̏��
	DirectX::SimpleMath::Vector3 m_pos;
	DirectX::SimpleMath::Quaternion m_rotation;
	DirectX::SimpleMath::Vector3 m_velocity;
	//����
	const float m_speed = 3.0f;
	//�����x
	float m_acceleration;

	const float MAX_ACCELERATION;
	const float MIN_ACCELERATION;

	//�p�x
	float m_angle = 0.0f;
	//�i����̃X�s�[�h
	float evoSpeed = 1.0f;
	//�S�[��������
	int m_goalCount = 0;
	//�|�C���g�̐�
	int m_maxGoalFlag;
	//�|�C���g�̉�
	int m_goalFlag = 0;
	//���݂̃|�C���g
	int m_point = 0;

	bool m_startFlag;
	DirectX::SimpleMath::Vector3 v3;

	//�傫��
	DirectX::SimpleMath::Vector3 m_size = { 2.0f,2.0f,2.0f };

	//�p�x
	DirectX::SimpleMath::Vector3 m_ang01 = { 0.0f,1.0f,0.0f };

	DirectX::SimpleMath::Quaternion m_rot01;

	bool m_hitFlag;
	bool m_hitFlag2;
	bool m_fla;
	BoxNode m_box;

	SphereNode m_sphere;
	bool m_engine;
};

