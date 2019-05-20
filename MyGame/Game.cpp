#include "Game.h"
#include "MyGame\GameSystem\InputManager.h"
#include "MyGame\GameSystem\DrawManager.h"

void ExitGame();

// コンストラクタ
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

// 実行に必要となるDirect3Dリソースを初期化する
void Game::Initialize()
{
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

// 基本ゲームループを実行する 
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

// ワールドを更新する 
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

	//SceneManagerの更新用処理
	m_sceneManager->UpdateActiveScene(timer);
}

// シーンを描画する
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
	DrawFPS();


	//SceneManagerの描画用処理
	m_sceneManager->RenderActiveSceneRender();
	
	m_spriteBatch->End();
	// バックバッファをスクリーンに送る 
	Present();
}

// FPSを描画する 
void Game::DrawFPS()
{
	// FPS文字列を生成する
	std::wstring fpsString = L"fps = " + std::to_wstring((unsigned int)m_timer.GetFramesPerSecond());
	// FPSを描画する Draw FPS
	m_font->DrawString(m_spriteBatch.get(), fpsString.c_str(), DirectX::SimpleMath::Vector2(0, 0), DirectX::Colors::White);
}

// バックバッファをクリアするためのヘルパー関数 
void Game::Clear()
{
	// レンダーターゲットをクリアする 
	m_directX.GetContext()->ClearRenderTargetView(m_directX.GetRenderTargetView().Get(), DirectX::Colors::Black);
	// デプスステンシルビューを設定する 
	m_directX.GetContext()->ClearDepthStencilView(m_directX.GetDepthStencilView().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	// レンダータッゲートを設定する 
	m_directX.GetContext()->OMSetRenderTargets(1, m_directX.GetRenderTargetView().GetAddressOf(), m_directX.GetDepthStencilView().Get());
	// ビューポートを設定する 
	CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(m_width), static_cast<float>(m_height));
	m_directX.GetContext()->RSSetViewports(1, &viewport);
}

// バックバッファをスクリーンに送る
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

// 終了処理をおこなう
void Game::Finalize()
{
	// Graphicsオブジェクトをリセットする
	DirectX11::Dispose();
	// Windowオブジェクトをリセットする
	m_window.reset();
}

// メッセージハンドラ 
void Game::OnActivated()
{
	// TODO: ゲームがアクティブなウィンドウになる 
}

void Game::OnDeactivated()
{
	// TODO: ゲームがバックグラウンドウィンドウになる 
}

void Game::OnSuspending()
{
	// TODO: ゲームがパワーサスペンデッドになる 
}

void Game::OnResuming()
{
	m_timer.ResetElapsedTime();

	// TODO: ゲームがパワーレジュームになる 
}

void Game::OnWindowSizeChanged(int width, int height)
{
	m_width = std::max(width, 1);
	m_height = std::max(height, 1);

	DirectX11::Get().CreateResources();
	// TODO: ゲームウィンドウのサイズが再変更される 
}

// プロパティ Properties
void Game::GetDefaultSize(int& width, int& height) const
{
	// TODO: 任意のデフォルトウィンドウサイズに変更する(最小サイズは320x200) 
	width = 800;
	height = 600;
}

// Exitヘルパー関数 
void ExitGame()
{
	PostQuitMessage(0);
}
