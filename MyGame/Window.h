//------------------------//------------------------
// Contents(処理内容) Flag.hの内容を書く
//------------------------//------------------------
// user(作成者) Keishi Teramoto
// Created date(作成日) 2019 / 06 / 20
// last updated (最終更新日) 2019 / 06 / 20
//------------------------//------------------------

// 多重インクルードの防止 ==================================================

#pragma once
#ifndef  WINDOW_DEFINED
#define  WINDOW_DEFINED
// ヘッダファイルの読み込み ================================================

#include <windows.h>
#include <mouse.h>
#include <keyboard.h>

#include "Game.h"
//----------------------------------------------------------------------
//!
//! @brief Windowクラス
//!
//----------------------------------------------------------------------

class Window 
{
public:
	// コンストラクタ
	Window(HINSTANCE hInstance, int nCmdShow) : m_hInstance(hInstance), m_nCmdShow(nCmdShow) {
	}
	// クラスを登録しウィンドウを生成する 
	int Initialize(int width, int height) 
	{
		// クラスを登録する
		WNDCLASSEX wcex;
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = m_hInstance;
		wcex.hIcon = LoadIcon(m_hInstance, L"IDI_ICON");
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = nullptr;
		wcex.lpszClassName = L"DirectXgameFrameworkWindowClass";
		wcex.hIconSm = LoadIcon(wcex.hInstance, L"IDI_ICON");
		// クラスを登録する
		if (!RegisterClassEx(&wcex))
			return 1;

		// ウィンドウを生成する
		RECT rc;
		rc.top = 0;
		rc.left = 0;
		rc.right = static_cast<LONG>(width);
		rc.bottom = static_cast<LONG>(height);

		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
		// ウィンドウを生成する
		HWND hWnd = CreateWindowEx(0, L"DirectXgameFrameworkWindowClass", L"DirectXgameFramework", WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, m_hInstance, nullptr);

		// TODO: CreateWindowEx(WS_EX_TOPMOST, L"DirectXgameFrameworkWindowClass", L"DirectXgameFramework", WS_POPUP,...)
		// にして規定でフルスクリーンに変更する

		if (!hWnd)
			return 1;

		ShowWindow(hWnd, m_nCmdShow);
		// TODO: nCmdShowにSW_SHOWMAXIMIZEDをセットして規定でフルスクリーンに変更する
		// Change nCmdShow to SW_SHOWMAXIMIZED to default to fullscreen.
		// SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(g_game.get()));

		// GetClientRect(hwnd, &rc);
		// Initialize window
		// g_game->Initialize(hwnd, rc.right - rc.left, rc.bottom - rc.top);
		m_hWnd = hWnd;
		return 0;
	}

	HWND GetHWnd() 
	{ 
		return m_hWnd; 
	}
	// ウィンドウプロシージャ
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	HWND m_hWnd;
	HINSTANCE m_hInstance;
	int m_nCmdShow;
};

#endif	// WINDOW_DEFINED

