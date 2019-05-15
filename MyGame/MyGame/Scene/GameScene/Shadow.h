//--------------------------------------------------------------------------------------
// File: Shadow.h
//
// 影クラス（Objectに付ける影）
//
// Date: 2018.12.5
// Author: Keishi Teramoto
//--------------------------------------------------------------------------------------
#pragma once

class Shadow
{
private:

	// モデルハンドル
	DirectX::Model* m_model;

	// 表示フラグ
	bool m_active;

	// ブレンドステート
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_blendState;
	ID3D11Device* m_device;
public:
	// コンストラクタ
	Shadow();

	// 初期化関数
	void Initialize(DirectX::Model* model,ID3D11Device* device);

	// 描画関数
	void Render();

	// 表示のON/OFFする関数
	void Active(bool flag) { m_active = flag; }
};
