﻿//------------------------//------------------------
// Contents(処理内容) Game.cppの内容を書く
//------------------------//------------------------
// user(作成者) Keishi Teramoto
// Created date(作成日) 2018 / 07 / 13
// last updated (最終更新日) 2018 / 11 / 05
//------------------------//------------------------



//インクルードファイルの宣言
#include "Game.h"
#include "CheckMemory.h"

#include "MyGame\GameSystem\InputManager.h"
#include "MyGame\GameSystem\DrawManager.h"
void ExitGame();

//----------------------------------------------------------------------
//! @brief Gameクラスのコンストラクタ
//!
//! @param なし
//!
//! @return なし
//----------------------------------------------------------------------
Game::Game(int width, int height)
	: m_hWnd(0), m_width(width), m_height(height) {

	// スタートアップ情報
	STARTUPINFO si{};
	// インスタンスハンドルを取得する
	m_hInstance = ::GetModuleHandle(NULL);

	// STARTUPINFO構造体の内容を取得する
	::GetStartupInfo(&si);
	m_nCmdShow = si.dwFlags & STARTF_USESHOWWINDOW ? si.wShowWindow : SW_SHOWDEFAULT;
	// Windowオブジェクトを生成する
	m_window = std::make_unique<Window>(m_hInstance, m_nCmdShow);
}

//----------------------------------------------------------------------
//! @brief Gameクラスの初期化処理
//!
//! @param なし
//!
//! @return なし
//----------------------------------------------------------------------
void Game::Initialize()
{
	// 実行に必要となるDirect3Dリソースを初期化する

	// Windowオブジェクトを初期化する
	m_window->Initialize(m_width, m_height);
	// Windowオブジェクトの生成後にウィンドウハンドルを取得する
	m_hWnd = m_window->GetHWnd();

	// DirectXの初期化のためウィンドウハンドルを設定する
	m_directX.SetHWnd(m_hWnd);
	// DirectXの初期化のためウィンドウ幅を設定する
	m_directX.SetWidth(m_width);
	// DirectXの初期化のためウィンドウ高を設定する
	m_directX.SetHeight(m_height);

	// デバイスを生成する Create Device
	m_directX.CreateDevice();
	// リソースを生成する Create Resources
	m_directX.CreateResources();

	// TODO: デフォルト変数timestepモード以外のものが必要な場合タイマー設定を変更する
	// 例えば 60 FPS固定タイムステップ更新ロジックに対しては以下を呼び出す
	// Change the timer settings if you want something other than the default variable timestep mode.
	// e.g. for 60 FPS fixed timestep update logic, call:

	// timer.SetFixedTimeStep(true);
	// timer.SetTargetElapsedSeconds(1.0 / 60);

	// TODO: 初期化コードを追加する 

	//音の作成処理
	//MyLibrary::ADX2Le::GetInstance()->Initialize(L"a.acf");

	// キーボードの作成
	m_keyboard = std::make_unique<DirectX::Keyboard>();

	// SpriteBatchオブジェクトを生成する
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(m_directX.GetContext().Get());
	// Fontオブジェクトを生成する
	m_font = std::make_unique<DirectX::SpriteFont>(m_directX.GetDevice().Get(), L"SegoeUI_18.spritefont");
	//描画用のマネージャーのイニシャライズ
	System::DrawManager::GetInstance().Initialize(m_directX.GetDevice().Get(), m_directX.GetContext().Get());

	//SceneManagerを生成する
	m_sceneManager = std::make_unique<SceneManager>();
	//SceneManagerの初期化処理
	m_sceneManager->InitilizeActiveScene();
	//SceneManagerの設定処理
	m_sceneManager->SetScene(TITLE_SCENE);

}

//----------------------------------------------------------------------
//! @brief Gameクラスの基本ゲームループを実行する 
//!
//! @param なし
//!
//! @return なし
//----------------------------------------------------------------------
MSG Game::Tick()
{
	// メッセージ 
	MSG msg = {};

	// Gameオブジェクトを初期化する
	Initialize();

	// ゲームループ
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// ゲームを更新する 
			m_timer.Tick([&]() { Update(m_timer); });
			// シーンを描画する 
			Render();
		}
	}

	// 終了処理をおこなう
	Finalize();
	
	return msg;
}


//----------------------------------------------------------------------
//! @brief Gameクラスの更新処理
//!
//! @param timer
//!
//! @return なし
//---------------------------------------------------------------------- 
void Game::Update(const DX::StepTimer& timer)
{
	float elapsedTime = float(timer.GetElapsedSeconds());

	// TODO: ゲームロジックを追加する Add your game logic here

	// キーボードの作成
	DirectX::Keyboard::State kb = m_keyboard->GetState();

	// キーボードトラッカーの更新
	m_keyboardTracker.Update(kb);

	// 入力クラスの更新
	System::InputManager::GetInstance().Update(&kb, &m_keyboardTracker);

	m_timer.SetFixedTimeStep(true);
	m_timer.SetTargetElapsedSeconds(1.0 / 60);

	//Spaceを押された場合
	if (System::InputManager::GetInstance().GetKeyboardState().Escape)
	{
		//ゲームの終了させる処理
		ExitGame();
	}

	//SceneManagerの更新用処理
	m_sceneManager->UpdateActiveScene(timer);
}

//----------------------------------------------------------------------
//! @brief Gameクラスの描画処理
//!
//! @param なし
//!
//! @return なし
//----------------------------------------------------------------------
void Game::Render()
{
	// 最初の更新の前は何も描画しないようにする
	if (m_timer.GetFrameCount() == 0)
	{
		return;
	}
	// 画面をクリアする
	Clear();

	// TODO: レンダリングコードを追加する
	m_spriteBatch->Begin();

	// FPSを描画する

	#ifdef _DEBUG

	DrawFPS();

	#endif

	//SceneManagerの描画用処理
	m_sceneManager->RenderActiveSceneRender();
	
	m_spriteBatch->End();
	// バックバッファをスクリーンに送る 
	Present();
}

//----------------------------------------------------------------------
//! @brief GameクラスのFPS描画関数
//!
//! @param なし
//!
//! @return なし
//---------------------------------------------------------------------- 
void Game::DrawFPS()
{
	// FPS文字列を生成する
	std::wstring fpsString = L"fps = " + std::to_wstring((unsigned int)m_timer.GetFramesPerSecond());
	// FPSを描画する Draw FPS
	m_font->DrawString(m_spriteBatch.get(), fpsString.c_str(), DirectX::SimpleMath::Vector2(0, 0), DirectX::Colors::White);
}

//----------------------------------------------------------------------
//! @brief Gameクラスのバックバッファをクリアするためのヘルパー関数 
//!
//! @param なし
//!
//! @return なし
//----------------------------------------------------------------------
void Game::Clear()
{
	// レンダーターゲットをクリアする 
	m_directX.GetContext()->ClearRenderTargetView(m_directX.GetRenderTargetView().Get(),DirectX::Colors::DarkBlue);
	// デプスステンシルビューを設定する 
	m_directX.GetContext()->ClearDepthStencilView(m_directX.GetDepthStencilView().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	// レンダータッゲートを設定する 
	m_directX.GetContext()->OMSetRenderTargets(1, m_directX.GetRenderTargetView().GetAddressOf(), m_directX.GetDepthStencilView().Get());
	// ビューポートを設定する 
	CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(m_width), static_cast<float>(m_height));
	m_directX.GetContext()->RSSetViewports(1, &viewport);
}

//----------------------------------------------------------------------
//! @brief Gameクラスの0バックバッファをスクリーンに送る
//!
//! @param なし
//!
//! @return なし
//---------------------------------------------------------------------- 
void Game::Present()
{
	// The first argument instructs DXGI to block until VSync, putting the application
	// to sleep until the next VSync. This ensures we don't waste any cycles rendering
	// frames that will never be displayed to the screen.

	HRESULT hr = m_directX.GetSwapChain()->Present(1, 0);

	// デバイスがリセットされた場合レンダラを再初期化する必要がある 
	if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
	{
		m_directX.OnDeviceLost();
	}
	else {
		DX::ThrowIfFailed(hr);
	}
}


//----------------------------------------------------------------------
//! @brief Gameクラスの終了処理
//!
//! @param なし
//!
//! @return なし
//------------------------fTI---------------------------------------------- 
void Game::Finalize()
{
	// Graphicsオブジェクトをリセットする
	DirectX11::Dispose();
	m_window.reset();
	m_graphics.reset();
	m_keyboard.reset();
	m_spriteBatch.reset();
	m_font.reset();
	m_commonStates.reset();
	// Windowオブジェクトをリセットする
	m_window.reset();
	
	if (m_sceneManager != nullptr)
	{
		m_sceneManager->FinalizeActiveScene();
		m_sceneManager.reset();
		m_sceneManager = nullptr;
	}
}

//----------------------------------------------------------------------
//! @brief Gameクラスのメッセージハンドラ
//!
//! @param なし
//!
//! @return なし
//---------------------------------------------------------------------- 
void Game::OnActivated()
{
	// TODO: ゲームがアクティブなウィンドウになる 
}
//----------------------------------------------------------------------
//! @brief Gameクラスのゲームがバックグラウンドウィンドウになる 
//!
//! @param なし
//!
//! @return なし
//---------------------------------------------------------------------- 
void Game::OnDeactivated()
{
	// TODO: ゲームがバックグラウンドウィンドウになる 
}
//----------------------------------------------------------------------
//! @brief Gameクラスのゲームがパワーサスペンデッドになる 
//!
//! @param なし
//!
//! @return なし
//---------------------------------------------------------------------- 

void Game::OnSuspending()
{
	// TODO: ゲームがパワーサスペンデッドになる 
}

//----------------------------------------------------------------------
//! @brief Gameクラスのゲームがパワーレジュームになる 
//!
//! @param なし
//!
//! @return なし
//---------------------------------------------------------------------- 
void Game::OnResuming()
{
	m_timer.ResetElapsedTime();

	// TODO: ゲームがパワーレジュームになる 
}
//----------------------------------------------------------------------
//! @brief Gameクラスのゲームサイズの変更
//!
//! @param なし
//!
//! @return なし
//---------------------------------------------------------------------- 

void Game::OnWindowSizeChanged(int width, int height)
{
	m_width = std::max(width, 1);
	m_height = std::max(height, 1);

	DirectX11::Get().CreateResources();
	// TODO: ゲームウィンドウのサイズが再変更される 
}
//----------------------------------------------------------------------
//! @brief Gameクラスの意のデフォルトウィンドウサイズに変更する
//!
//! @param なし
//!
//! @return なし
//---------------------------------------------------------------------- 
void Game::GetDefaultSize(int& width, int& height) const
{
	// TODO: 任意のデフォルトウィンドウサイズに変更する(最小サイズは320x200) 
	width = 800;
	height = 600;
}
//----------------------------------------------------------------------
//! @brief Exitヘルパー関数 
//!
//! @param なし
//!
//! @return なし
//---------------------------------------------------------------------- 
void ExitGame()
{
	PostQuitMessage(0);
}

