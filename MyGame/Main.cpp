//------------------------//------------------------
// Contents(処理内容) Main.cppの内容を書く
//------------------------//------------------------
// user(作成者) Keishi Teramoto
// Created date(作成日) 2019 / 05 / 30
// last updated (最終更新日) 2019 / 06 / 05
//------------------------//------------------------
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


#include "Window.h"
#include "CheckMemory.h"

#include "Game.h"


//----------------------------------------------------------------------
//! @brief メインソース
//!
//! @param なし
//!
//! @return なし
//----------------------------------------------------------------------
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	// メモリリークレポートを出力ウィンドウのデバッグウィンドウに出力する
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// 出力先を出力ウィンドウに戻す
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	//COMライブラリを初期化する。
	if (FAILED(CoInitializeEx(nullptr, COINITBASE_MULTITHREADED)))
		return 1;

	int width = 800;

	int height = 600;

	//Gameオブジェクトの生成
	Game game(width, height);
	//ゲームの実行をする
	MSG msg = game.Tick();

	//COMイニシャライズの終了処理(解放)
	CoUninitialize();
	return (int)msg.wParam;

}