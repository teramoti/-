//------------------------//------------------------
// Contents(�������e) Flag.h�̓��e������
//------------------------//------------------------
// user(�쐬��) Keishi Teramoto
// Created date(�쐬��) 2019 / 06 / 20
// last updated (�ŏI�X�V��) 2019 / 06 / 20
//------------------------//------------------------

// ���d�C���N���[�h�̖h�~ ==================================================

#pragma once
#ifndef  WINDOW_DEFINED
#define  WINDOW_DEFINED
// �w�b�_�t�@�C���̓ǂݍ��� ================================================

#include <windows.h>
#include <mouse.h>
#include <keyboard.h>

#include "Game.h"
//----------------------------------------------------------------------
//!
//! @brief Window�N���X
//!
//----------------------------------------------------------------------

class Window 
{
public:
	// �R���X�g���N�^
	Window(HINSTANCE hInstance, int nCmdShow) : m_hInstance(hInstance), m_nCmdShow(nCmdShow) {
	}
	// �N���X��o�^���E�B���h�E�𐶐����� 
	int Initialize(int width, int height) 
	{
		// �N���X��o�^����
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
		// �N���X��o�^����
		if (!RegisterClassEx(&wcex))
			return 1;

		// �E�B���h�E�𐶐�����
		RECT rc;
		rc.top = 0;
		rc.left = 0;
		rc.right = static_cast<LONG>(width);
		rc.bottom = static_cast<LONG>(height);

		AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
		// �E�B���h�E�𐶐�����
		HWND hWnd = CreateWindowEx(0, L"DirectXgameFrameworkWindowClass", L"DirectXgameFramework", WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, m_hInstance, nullptr);

		// TODO: CreateWindowEx(WS_EX_TOPMOST, L"DirectXgameFrameworkWindowClass", L"DirectXgameFramework", WS_POPUP,...)
		// �ɂ��ċK��Ńt���X�N���[���ɕύX����

		if (!hWnd)
			return 1;

		ShowWindow(hWnd, m_nCmdShow);
		// TODO: nCmdShow��SW_SHOWMAXIMIZED���Z�b�g���ċK��Ńt���X�N���[���ɕύX����
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
	// �E�B���h�E�v���V�[�W��
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	HWND m_hWnd;
	HINSTANCE m_hInstance;
	int m_nCmdShow;
};

#endif	// WINDOW_DEFINED

