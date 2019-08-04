//--------------------------------------------------------------------------------------
// File: Shadow.h
//
// �e�N���X�iObject�ɕt����e�j
//
// Date: 2018.12.5
// Author: Keishi Teramoto
//--------------------------------------------------------------------------------------
#pragma once
#include <d3d11.h>
#include <wrl.h>
#include<wrl\client.h>
#include <SimpleMath.h>
#include <Model.h>
#include "../../GameSystem/Object.h"

#include "TpsCamera.h"
#include "../../Utillity/DirectX11.h"

class Shadow 
{
private:

	// ���f���n���h��
	std::unique_ptr<DirectX::Model> m_model;

	// �\���t���O
	bool m_active;

	// �u�����h�X�e�[�g
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_blendState;

	DirectX11& m_directX11 = DirectX11::Get();
public:
	// �R���X�g���N�^
	Shadow();
	//�@�f�X�g���N�^
	~Shadow();
	// �������֐�
	void Initialize();

	// �`��֐�
	void Render(DirectX::SimpleMath::Matrix& view , DirectX::SimpleMath::Matrix& proj, Teramoto::Object3D* setObject,float objectHeight);

	// �\����ON/OFF����֐�
	void Active(bool flag) { m_active = flag; }
};
