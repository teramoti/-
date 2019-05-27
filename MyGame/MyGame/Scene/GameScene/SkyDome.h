//----------------------------------------
/// <summary>
/// �R�[�X�̃N���X
/// GS2 ���{ �[�u
/// </summary>
//----------------------------------------
#pragma once
#include <d3d11.h>
#include <SimpleMath.h>
#include "../../GameSystem/Object.h"

class SkyDome : public MyLib::Object3D
{
public:
	const float SKYDOME_ROTATION_Y = 0.005f;
public:
	SkyDome();
	~SkyDome();
public:

	void Initilize();
	void Update();
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	void CreateResource();

	void SetLight();

private:
	std::unique_ptr<DirectX::Model> m_model;

};