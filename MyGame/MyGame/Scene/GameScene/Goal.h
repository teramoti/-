#pragma once


#include <Model.h>
#include <CommonStates.h>

#include <Effects.h>
#include "TpsCamera.h"
#include "../../Collison/Collision.h"
#include "../../GameSystem/Object.h"
#include "../../Utillity/DirectX11.h"
#include "Shadow.h"

class GoalObject : public Teramoto::Object3D
{

public:
	//�R���X�g���N�^
	GoalObject();
	//�f�X�g���N�^
	~GoalObject();
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

private:
	std::unique_ptr<DirectX::Model> m_model;
	
	DirectX11& m_directX = DirectX11::Get();
};

