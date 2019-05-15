//------------------------//------------------------
// Contents(処理内容) Game.hの内容を書く
//------------------------//------------------------
// user(作成者) Keishi Teramoto
// Created date(作成日) 2018 / 07 / 13
// last updated (最終更新日) 2018 / 11 / 05
//------------------------//------------------------


// 多重インクルードの防止 ==================================================
#pragma once

// ヘッダファイルの読み込み ================================================
#include "StepTimer.h"
#include <CommonStates.h>
#include "DeviceResources.h"
#include "MyGame\Scene\SceneManager\SceneManager.h"

//----------------------------------------------------------------------
//!
//! @brief D3D11デバイスを作成する基本的なゲームの実装ループをするクラス
//!
//----------------------------------------------------------------------
class Game : public DX::IDeviceNotify
{
public:
	// コンストラクタ
	Game();

	// 初期化処理
	void Initialize(HWND window, int width, int height);

	// ゲームループ処理
	void Tick();

	// デバイス解放処理
	virtual void OnDeviceLost() override;

	// デバイスの復元処理
	virtual void OnDeviceRestored() override;

	// 活性化処理
	void OnActivated();

	//　無効処理
	void OnDeactivated();

	// 一時停止処理
	void OnSuspending();

	// 再開処理
	void OnResuming();

	// ウィンドウサイズ変更処理
	void OnWindowSizeChanged(int width, int height);

	// デフォルトサイズを取得処理
	void GetDefaultSize(int& width, int& height) const;

	// フルスクリーンモードに切り替える関処理
	void ChangeFullScreen(BOOL flag);

private:
	// 更新処理
	void Update(DX::StepTimer const& timer);

	// 描画処理
	void Render();

	// クリア処理
	void Clear();

	// デバイスの依存リソースの作成処理
	void CreateDeviceDependentResources();

	// ウィンドウサイズの依存リソースの作成処理
	void CreateWindowSizeDependentResources();

private:
	//変数宣言

	// デバイスリソース
	std::unique_ptr<DX::DeviceResources>    m_deviceResources;

	// ループタイマー
	DX::StepTimer                           m_timer;

	// キーボード
	std::unique_ptr<DirectX::Keyboard>      m_keyboard;

	// キーボードトラッカー
	DirectX::Keyboard::KeyboardStateTracker m_keyboardTracker;

	// コモンステート
	std::unique_ptr<DirectX::CommonStates>  m_states;

	// スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch>   m_sprites;

	// ワールド行列
	DirectX::SimpleMath::Matrix             m_world;

	// ビュー行列
	DirectX::SimpleMath::Matrix             m_view;

	// 射影行列
	DirectX::SimpleMath::Matrix             m_projection;

	// タスクマネージャ
	std::unique_ptr<SceneManager>			 m_SceneManager;
	// スクリーンの横幅
	int										m_screenWidth;

	// スクリーンの縦幅
	int										m_screenHeight;

	const wchar_t* m_acf;
};