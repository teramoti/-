#pragma once


#include <Model.h>
#include <CommonStates.h>

#include <Effects.h>
#include "../../Scene/GameScene/TpsCamera.h"
#include "../../Collison/Collision.h"
#include "../../GameSystem/Object.h"
#include "../../Utillity/DirectX11.h"
#include "../GameScene/Shadow.h"

class TitleGoalObject : public Teramoto::Object3D
{

public:
	//�R���X�g���N�^
	TitleGoalObject();
	//�f�X�g���N�^
	~TitleGoalObject();
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

