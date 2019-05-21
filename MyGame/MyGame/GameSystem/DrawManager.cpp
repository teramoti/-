//#include "../../pch.h"
#include "../Utillity/dx.h"

#include <CommonStates.h>

#include "DrawManager.h"

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="devise">デバイス</param>
void System::DrawManager::Initialize(ID3D11Device* pDevise, ID3D11DeviceContext* pContext)
{
	SetDevise(pDevise);


	mSpriteBatch = std::make_unique<DirectX::SpriteBatch>(pContext);
}

/// <summary>
/// 描画
/// </summary>
/// <param name="data">描画データ構造体</param>
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
/// 描画前後処理
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
/// テクスチャ読み込み
/// </summary>
/// <param name="pData">描画データ構造体</param>
/// <param name="fileName">ファイル名</param>
/// <returns>成功かどうか</returns>
bool System::DrawManager::LoadTexture(DrawData& data, wchar_t* pFileName)
{
	// デバイスが無いので失敗
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
	// デバイスが無いので失敗
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