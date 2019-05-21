//------------------------//------------------------
// Contents(処理内容) Game.hの内容を書く
//------------------------//------------------------
// user(作成者) Keishi Teramoto
// Created date(作成日) 2018 / 07 / 13
// last updated (最終更新日) 2018 / 11 / 05
//------------------------//------------------------

#ifndef GAME_DEFINED
#define GAME_DEFINED

// Use the C++ standard templated min/max
#define NOMINMAX

//インクルードファイルの宣言
#include <windows.h>
#include <iostream>
#include <string>
#include <iomanip>

#include <d3d11.h>
#include <memory>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <Model.h>
#include <Keyboard.h>
#include <GeometricPrimitive.h>
#include <WICTextureLoader.h>
#include <algorithm>
#include <CommonStates.h>

#include "StepTimer.h"
#include "MyGame\\Utillity\\dx.h"
#include "Window.h"
#include "MyGame\\Utillity\\DirectX11.h"
#include "MyGame\Scene\SceneManager\SceneManager.h"

class Window;

// ゲームを実装する 
class Game
{
public:
	// コンストラクタ
	Game(int width, int height);
	// ゲームに必要なオブジェクトを初期する
	void Initialize();
	// 基本ゲームループを実行する
	MSG Tick();
	// 終了処理をおこなう
	void Finalize();

	// メッセージ Messages
	void OnActivated();
	void OnDeactivated();
	void OnSuspending();
	void OnResuming();
	void OnWindowSizeChanged(int width, int height);

	// プロパティ 
	void GetDefaultSize(int& width, int& height) const;

private:
	// ゲームを更新する 
	void Update(const DX::StepTimer& timer);
	// シーンを描画する 
	void Render();
	// 画面をクリアする 
	void Clear();
	// バックバッファをスクリーンに送る
	void Present();
	// FPSを描画する 
	void DrawFPS();

private:
	// インスタンスハンドル
	HINSTANCE m_hInstance;
	// 実行時のウィンドウの大きさ
	int m_nCmdShow;
	// デバイスリソース 
	HWND m_hWnd;
	// 出力幅
	int m_width;
	// 出力高
	int m_height;

	// ウィンドウ 
	std::unique_ptr<Window> m_window;
	// グラフィックス 
	std::unique_ptr<DirectX11> m_graphics;
	// ループタイマーを描画する 
	DX::StepTimer m_timer;

	// キーボード 
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	// キーボードトラッカー
	DirectX::Keyboard::KeyboardStateTracker m_keyboardTracker;

	// スプライトバッチ 
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	// フォント Font
	std::unique_ptr<DirectX::SpriteFont> m_font;

	// エフェクトファクトリインターフェース 
	//std::unique_ptr<IEffectFactory> m_fxFactory;
	// コモンステート
	std::unique_ptr<DirectX::CommonStates> m_commonStates;

	// Graphicsクラスのインスタンスを取得する
	DirectX11& m_directX = DirectX11::Get();
	//SceneManagerクラス
	std::unique_ptr<SceneManager> m_sceneManager;

};

#endif	// GAME_DEFINED

