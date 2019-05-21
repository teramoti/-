//#include "../../pch.h"
#include "../Utillity/dx.h"

#include <CommonStates.h>

#include "DrawManager.h"

/// <summary>
/// ����������
/// </summary>
/// <param name="devise">�f�o�C�X</param>
void System::DrawManager::Initialize(ID3D11Device* pDevise, ID3D11DeviceContext* pContext)
{
	SetDevise(pDevise);


	mSpriteBatch = std::make_unique<DirectX::SpriteBatch>(pContext);
}

/// <summary>
/// �`��
/// </summary>
/// <param name="data">�`��f�[�^�\����</param>
void System::DrawManager::Draw(DrawData& data)
{
	mSpriteBatch->Draw(
		(*data.GetTexture()),
		data.GetPos(),
		data.GetRectPtn(),
		DirectX::Colors::White,
		data.GetRot(),
		data.GetOrigin(),
		data.GetScale()
	);
}

/// <summary>
/// �`��O�㏈��
/// </summary>
void System::DrawManager::Begin()
{
	DirectX::CommonStates states(mpDevice);

	mSpriteBatch->Begin(DirectX::SpriteSortMode_Deferred, states.NonPremultiplied());

}
void System::DrawManager::End()
{
	mSpriteBatch->End();
}

/// <summary>
/// �e�N�X�`���ǂݍ���
/// </summary>
/// <param name="pData">�`��f�[�^�\����</param>
/// <param name="fileName">�t�@�C����</param>
/// <returns>�������ǂ���</returns>
bool System::DrawManager::LoadTexture(DrawData& data, wchar_t* pFileName)
{
	// �f�o�C�X�������̂Ŏ��s
	if (mpDevice == NULL)
	{
		return false;
	}

	DX::ThrowIfFailed
	(
		DirectX::CreateWICTextureFromFile
		(
			mpDevice,
			pFileName,
			nullptr,
			data.GetTexture()
		)
	);

	return true;
}

bool System::DrawManager::LoadTexture(DxTexture& pTexture, wchar_t* pFileName)
{
	// �f�o�C�X�������̂Ŏ��s
	if (mpDevice == NULL)
	{
		return false;
	}


	DX::ThrowIfFailed
	(
		DirectX::CreateWICTextureFromFile
		(
			mpDevice,
			pFileName,
			nullptr,
			&pTexture
		)
	);

	return true;
}