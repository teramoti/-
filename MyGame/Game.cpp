//------------------------//------------------------
// Contents(処理内容) Game.cppの内容を書く
//------------------------//------------------------
// user(作成者) Keishi Teramoto
// Created date(作成日) 2018 / 07 / 13
// last updated (最終更新日) 2018 / 11 / 05
//------------------------//------------------------

//インクルードファイルの宣言
#include "pch.h"
#include "Game.h"
#include "MyGame\GameSystem\DrawManager.h"
#include "MyGame\GameSystem\InputManager.h"
#include "MyGame\ADX2\ADX2Le.h"

// 名前空間の使用 ==========================================================
using namespace DirectX;
using namespace DirectX::SimpleMath;
using Microsoft::WRL::ComPtr;


#pragma region Game
#pragma region Frame Initialize
#pragma region Game Constructor
//----------------------------------------------------------------------
//! @brief ゲームのコンストラクタ
//!
//! @param なし
//!
//! @return なし
//----------------------------------------------------------------------
Game::Game()
{
	// デバイスリソースの作成
	m_deviceResources = std::make_unique<DX::DeviceResources>();

	// デバイス登録通知
	m_deviceResources->RegisterDeviceNotify(this);

	// スクリーンの横幅の設定
	m_screenWidth = 800;
	// スクリーンの縦幅の設定
	m_screenHeight = 600;
	m_acf = L"MyGame.acf";//ファイル名を入れる
}
#pragma endregion

#pragma region Game Initialize
//----------------------------------------------------------------------
//! @brief ゲームの初期化処理
//!
//! @param [HWND window, int width, int height]
//!
//! @return なし
//----------------------------------------------------------------------
void Game::Initialize(HWND window, int width, int height)
{
#pragma region Initialization Processing


	//----------------------------------------------------------------------
	// ここからゲームの初期化処理を記述する
	//----------------------------------------------------------------------
	// キーボードの作成
	m_keyboard = std::make_unique<Keyboard>();

	// ウィンドウの設定
	m_deviceResources->SetWindow(window, width, height);

	// デバイスリソースの作成
	m_deviceResources->CreateDeviceResources();

	// デバイス依存リソースの作成
	CreateDeviceDependentResources();

	// ウィンドウサイズに依存するリソースを作成する
	m_deviceResources->CreateWindowSizeDependentResources();

	// ウィンドウサイズに依存するリソースを作成する
	CreateWindowSizeDependentResources();

	//音の設定をする
	MyLibrary::ADX2Le::GetInstance()->Initialize(m_acf);

	//描画用のマネージャーのイニシャライズ
	System::DrawManager::GetInstance().Initialize(m_deviceResources->GetD3DDevice(), m_deviceResources->GetD3DDeviceContext());
	//シーンマネージャーを作る
	m_SceneManager = std::make_unique<SceneManager>(m_deviceResources->GetD3DDevice(), m_deviceResources->GetD3DDeviceContext());
	//シーンマネージャーのイニシャライズを呼ぶ
	m_SceneManager->InitilizeActiveScene(m_screenWidth, m_screenHeight);
	//シーンマネージャーにシーンをセットする
	m_SceneManager->SetScene(TITLE_SCENE, m_screenWidth, m_screenHeight);


	//マウスを消す
	//ShowCursor(false);

	// サウンドの読み込み

	//----------------------------------------------------------------------
	// ここまで
	//----------------------------------------------------------------------
#pragma endregion
}
#pragma endregion
#pragma endregion

#pragma region Frame Update
#pragma region Game Loop
//----------------------------------------------------------------------
//! @brief ゲームループ処理
//!
//! @param なし
//!
//! @return なし
//----------------------------------------------------------------------
void Game::Tick()
{
	// ループタイマーの更新
	m_timer.Tick([&]()
	{
		// ゲームの更新
		Update(m_timer);
	});

	// 描画
	Render();
}
#pragma endregion

#pragma region Game Update
//----------------------------------------------------------------------
//! @brief ゲームの更新処理
//!
//! @param [DX::StepTimer const& timer]
//!
//! @return なし
//----------------------------------------------------------------------
void Game::Update(DX::StepTimer const& timer)
{
	float elapsedTime = float(timer.GetElapsedSeconds());

#pragma region Game Logic
	//----------------------------------------------------------------------
	// ここからゲームロジックを記述する
	//----------------------------------------------------------------------

	elapsedTime;

	// キーボードの作成
	Keyboard::State kb = m_keyboard->GetState();

	// キーボードトラッカーの更新
	m_keyboardTracker.Update(kb);

	// 入力クラスの更新
	System::InputManager::GetInstance().Update(&kb, &m_keyboardTracker);

	// タスクマネージャの更新
	m_SceneManager->UpdateActiveScene(timer);

	//----------------------------------------------------------------------
	// ここまで
	//----------------------------------------------------------------------
#pragma endregion
}
#pragma endregion
#pragma endregion

#pragma region Frame Render
#pragma region Game Render
//----------------------------------------------------------------------
//! @brief ゲームの描画処理
//!
//! @param なし
//!
//! @return なし
//----------------------------------------------------------------------
void Game::Render()
{
	// 最初の更新の前に何かを描画しないでください
	if (m_timer.GetFrameCount() == 0)
	{
		return;
	}
	Clear();

	// 描画開始処理
	m_deviceResources->PIXBeginEvent(L"Render");

	//----------------------------------------------------------------------
	// ここから描画処理を記述する
	//----------------------------------------------------------------------
	auto context = m_deviceResources->GetD3DDeviceContext();
	context;
	// タスクマネージャの描画
	m_SceneManager->RenderActiveSceneRender();

	//----------------------------------------------------------------------
	// 描画処理はここまで
	//----------------------------------------------------------------------

	//描画終了処理
	m_deviceResources->PIXEndEvent();

	// 新しいフレームを表示します
	m_deviceResources->Present();
}
#pragma endregion

#pragma region Game Clear
//----------------------------------------------------------------------
//! @brief ゲームのクリア処理
//!
//! @param なし
//!
//! @return なし
//----------------------------------------------------------------------
void Game::Clear()
{
	m_deviceResources->PIXBeginEvent(L"Clear");

	//----------------------------------------------------------------------
	// ビューのクリア処理
	//----------------------------------------------------------------------

	//デバイスコンテキストの取得処理
	auto context = m_deviceResources->GetD3DDeviceContext();

	// レンダリングターゲットビューの取得処理
	auto renderTarget = m_deviceResources->GetRenderTargetView();

	// ステンシルビューの取得処理
	auto depthStencil = m_deviceResources->GetDepthStencilView();

	// 描画ターゲットビューのクリア処理
	context->ClearRenderTargetView(renderTarget, Colors::MediumPurple);

	// クリア奥行きステンシルビュー処理
	context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// OMレンダーターゲットの設定処理
	context->OMSetRenderTargets(1, &renderTarget, depthStencil);

	//----------------------------------------------------------------------
	// ビューポートの設定処理
	//----------------------------------------------------------------------

	// スクリーンビューポートの取得処理
	auto viewport = m_deviceResources->GetScreenViewport();

	context->RSSetViewports(1, &viewport);
	m_deviceResources->PIXEndEvent();
}
#pragma endregion
#pragma endregion

#pragma region Message Handlers
//----------------------------------------------------------------------
//! @brief ゲームの活性化処理
//!
//! @param なし
//!
//! @return なし
//----------------------------------------------------------------------
void Game::OnActivated()
{

}

//----------------------------------------------------------------------
//! @brief ゲームの無効処理
//!
//! @param なし
//!
//! @return なし
//----------------------------------------------------------------------
void Game::OnDeactivated()
{

}

//----------------------------------------------------------------------
//! @brief ゲームの一時停止処理
//!
//! @param なし
//!
//! @return なし
//----------------------------------------------------------------------
void Game::OnSuspending()
{

}

//----------------------------------------------------------------------
//! @brief ゲームの再開処理
//!
//! @param なし
//!
//! @return なし
//----------------------------------------------------------------------
void Game::OnResuming()
{
	// 経過時間のリセット処理
	m_timer.ResetElapsedTime();
}

//----------------------------------------------------------------------
//! @brief ゲームのウィンドウサイズ変更処理
//!
//! @param [int width, int height]
//!
//! @return なし
//----------------------------------------------------------------------
void Game::OnWindowSizeChanged(int width, int height)
{
	if (!m_deviceResources->WindowSizeChanged(width, height))
		return;

	CreateWindowSizeDependentResources();

}

//----------------------------------------------------------------------
//! @brief ゲームのデフォルトサイズを取得処理
//!
//! @param [int& width, int& height]
//!
//! @return なし
//----------------------------------------------------------------------
void Game::GetDefaultSize(int& width, int& height) const
{
	// 希望のデフォルトウィンドウサイズに変更してください (最小サイズは 320x200)
	width = m_screenWidth;
	height = m_screenHeight;
}
#pragma endregion

#pragma region Direct3D Resources
//----------------------------------------------------------------------
//! @brief ゲームのデバイスの依存リソースの作成処理
//!
//! @param なし
//!
//! @return なし
//----------------------------------------------------------------------
void Game::CreateDeviceDependentResources()
{

	//----------------------------------------------------------------------
	// 作成処理を記入する
	//----------------------------------------------------------------------
	ID3D11Device* device = m_deviceResources->GetD3DDevice();
	ID3D11DeviceContext* context = m_deviceResources->GetD3DDeviceContext();

	// デバイス依存のオブジェクトをここで初期化する
	device;

	// コモンステートの作成
	m_states = std::make_unique<CommonStates>(device);

	// スプライトバッチの作成
	m_sprites = std::make_unique<SpriteBatch>(context);

}

//----------------------------------------------------------------------
//! @brief ゲームのウィンドウサイズの依存リソースの作成処理
//!
//! @param なし
//!
//! @return なし
//----------------------------------------------------------------------
void Game::CreateWindowSizeDependentResources()
{
	// ウインドウサイズからアスペクト比を算出する
	RECT size = m_deviceResources->GetOutputSize();
	float aspectRatio = float(size.right) / float(size.bottom);

	// 画角を設定
	float fovAngleY = XMConvertToRadians(45.0f);

	// 射影行列を作成する
	m_projection = Matrix::CreatePerspectiveFieldOfView(
		fovAngleY,
		aspectRatio,
		0.01f,
		1000.0f
	);
}

//----------------------------------------------------------------------
//! @brief ゲームのフルスクリーンモードに切り替える関処理
//!
//! @param [BOOL flag]
//!
//! @return なし
//----------------------------------------------------------------------
void Game::ChangeFullScreen(BOOL flag)
{

	m_deviceResources->GetSwapChain()->SetFullscreenState(flag, NULL);
}

//----------------------------------------------------------------------
//! @brief ゲームのデバイス解放処理
//!
//! @param なし
//!
//! @return なし
//----------------------------------------------------------------------
void Game::OnDeviceLost()
{
	//----------------------------------------------------------------------
	// ここから解放処理を記入してください
	//----------------------------------------------------------------------

	// デバイスリソースの解放
	m_deviceResources.reset();

	// キーボードの解放
	m_keyboard.reset();

	// コモンステートの解放
	m_states.reset();

	// スプライトバッチの解放
	m_sprites.reset();


	// すべての作業タスクを削除	
	//音を削除
	MyLibrary::ADX2Le::GetInstance()->Finalize();
	m_SceneManager->FinalizeActiveScene();
	m_SceneManager.reset();
	m_SceneManager = nullptr;



}

//----------------------------------------------------------------------
//! @brief ゲームのデバイスの復元処理
//!
//! @param なし
//!
//! @return なし
//----------------------------------------------------------------------
void Game::OnDeviceRestored()
{
	// デバイス依存リソースの作成処理
	CreateDeviceDependentResources();

	// ウィンドウサイズに依存するリソースの作成処理
	CreateWindowSizeDependentResources();
}
#pragma endregion
#pragma endregion