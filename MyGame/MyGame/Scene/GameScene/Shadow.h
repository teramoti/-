//--------------------------------------------------------------------------------------
// File: Shadow.h
//
// 影クラス（Objectに付ける影）
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

	// モデルハンドル
	std::unique_ptr<DirectX::Model> m_model;

	// 表示フラグ
	bool m_active;

	// ブレンドステート
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_blendState;

	DirectX11& m_directX11 = DirectX11::Get();
public:
	// コンストラクタ
	Shadow();
	//　デストラクタ
	~Shadow();
	// 初期化関数
	void Initialize();

	// 描画関数
	void Render(DirectX::SimpleMath::Matrix& view , DirectX::SimpleMath::Matrix& proj, Teramoto::Object3D* setObject,float objectHeight);

	// 表示のON/OFFする関数
	void Active(bool flag) { m_active = flag; }
};
