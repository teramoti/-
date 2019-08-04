#pragma once


#include <Model.h>
#include <CommonStates.h>

#include <Effects.h>
#include "TpsCamera.h"
#include "../../Collison/Collision.h"
#include "../../GameSystem/Object.h"
#include "Shadow.h"
#include "../../Utillity/DirectX11.h"

class MyAirPlane : public Teramoto::Object3D
{

public:
	//�R���X�g���N�^
	MyAirPlane();
	//�f�X�g���N�^
	~MyAirPlane();
public:

	//����������
	void Initilize(Shadow* shadow);
	void CreateResource();
	//�X�V����
	void Update(bool flag);
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


	Collision::Box& GetBox()
	{
		return *m_box;
	}

	void AddCoin()
	{
		m_coinNum += 1;
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
	const float GRAVITY=0.98f;
	//�ō����x
	const float MAX_ACCELERATION=45.0f;
	//�Œᑬ�x
	const float MIN_ACCELERATION= 0.0f;

public:
	//�p�x
	float m_angle;
	//�n�܂������̃t���O�Ǘ�
	bool m_startFlag;
	
	//���f���̒�`
	std::unique_ptr<DirectX::Model> m_model;
	//���x�p�ϐ�
	DirectX::SimpleMath::Vector3 vec;

	int m_coinNum;
	//�{�b�N�X��Node
	Collision::Box* m_box;

	DirectX11& m_directX = DirectX11::Get();
};

