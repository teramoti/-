//--------------------------------------------------------------------------------------
// File: Shadow.h
//
// �e�N���X�iObject�ɕt����e�j
//
// Date: 2018.12.5
// Author: Keishi Teramoto
//--------------------------------------------------------------------------------------
#pragma once

class Shadow
{
private:

	// ���f���n���h��
	DirectX::Model* m_model;

	// �\���t���O
	bool m_active;

	// �u�����h�X�e�[�g
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_blendState;
	ID3D11Device* m_device;
public:
	// �R���X�g���N�^
	Shadow();

	// �������֐�
	void Initialize(DirectX::Model* model,ID3D11Device* device);

	// �`��֐�
	void Render();

	// �\����ON/OFF����֐�
	void Active(bool flag) { m_active = flag; }
};
