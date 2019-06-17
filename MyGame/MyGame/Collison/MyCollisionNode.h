//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//
// �����蔻��m�[�h
//
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once

#include "../GameSystem/Object.h"
#include "MyCollision.h"
#include "../Utillity/DirectX11.h"
#include<Model.h>
// �����蔻��m�[�h 
class CollisionNode
{
protected:
	// �f�o�b�O�\��ON
	static bool m_DebugVisible;

public:
	CollisionNode();
	~CollisionNode();
	// setter
	static void SetDebugVisible(bool Visible) { m_DebugVisible = Visible; }

	// getter
	static bool GetDebugVisible() { return m_DebugVisible; }
	

	// ���f���n���h��
	std::unique_ptr<DirectX::Model> m_model;
protected:
// �����o�ϐ�
	//�f�o�b�O�\���p�I�u�W�F�N�g
	Teramoto::Object3D m_obj;

	DirectX::SimpleMath::Vector3 m_translation;

	DirectX11& m_directX11 = DirectX11::Get();
public:
// �����o�֐�
	// ����������
	virtual void Initialize() = 0;
	// �X�V����
	virtual void Update() = 0;
	// �`�揈��
	virtual void Render(DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj) = 0;

	virtual void CreateResource()=0;
	void SetParent(Teramoto::Object3D* parent);

	void SetTrans(DirectX::SimpleMath::Vector3& trans);

};

// ���̓����蔻��m�[�h //
class SphereNode : public CollisionNode , public MyCollision::Sphere
{
protected:
// �����o�ϐ�
	float m_localRadius;

public:
// �����o�֐�
	// �R���X�g���N�^
	SphereNode();
	// ����������
	void Initialize();
	// �X�V����
	void Update();
	// �`�揈��
	void Render(DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj);

	void CreateResource();

	void SetLocalRadius(float radius) { m_localRadius = radius;}

	// ���S���W���擾����
	DirectX::SimpleMath::Vector3 GetTrans() { return m_translation; }
};

class BoxNode :public CollisionNode, public MyCollision::Box
{
protected:
// �����o�ϐ�

	// �e�ӂ̑傫���ix:��,y:�c,z:���j
	DirectX::SimpleMath::Vector3 m_size;

public:
	// �R���X�g���N�^
	BoxNode();
	// ����������
	void Initialize();
	// �X�V����
	void Update();
	// �`�揈��
	void Render(DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj);

	void CreateResource();

	// �e�ӂ̑傫����ݒ肷��
	void SetSize(DirectX::SimpleMath::Vector3 size) { m_size = size;DirectX::SimpleMath::Vector3 Lsize = size /2; m_obj.SetScale(Lsize); 
	SetPointPos();
	}

	// �e�ӂ̑傫���Œ��_��ݒ肷��
	void SetPointPos();

	// ���S���W���擾����
	DirectX::SimpleMath::Vector3 GetTrans() { return m_translation; }

	// ���̑傫�����擾����
	DirectX::SimpleMath::Vector3 GetSize() { return m_size; }

};

class CapsuleNode :public CollisionNode, public MyCollision::Capsule
{
private:

	float m_height;

public:
	CapsuleNode();
	// ����������
	void Initialize();
	// �X�V����
	void Update();
	// �`�揈��
	void Render(DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj);

	void CreateResource();
	//�傫���̃Z�b�g
	void SetSize(DirectX::SimpleMath::Vector3 size);
	//���a�ƍ����̃Z�b�g
	void SetHiehtRadius(float height, float radius);

	void SetPos();

	//Sgment��End�̍��W���󂯎��H
	DirectX::SimpleMath::Vector3 GetTrans() { return m_translation; }
};

//����
class PlanarNode :public CollisionNode, public MyCollision::Planar
{
public:
	PlanarNode();

	void Initialize();

	void Update();

	void Render(DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj);

	void CreateResource();

	//�傫����ݒ肷��(�����`�A�����`��z��
	void SetVertex4(DirectX::SimpleMath::Vector3 Ver0, DirectX::SimpleMath::Vector3 Ver1, DirectX::SimpleMath::Vector3 Ver2, DirectX::SimpleMath::Vector3 Ver3);
};