//------------------------//------------------------
// Contents(�������e) Main.cpp�̓��e������
//------------------------//------------------------
// user(�쐬��) Keishi Teramoto
// Created date(�쐬��) 2019 / 05 / 30
// last updated (�ŏI�X�V��) 2019 / 06 / 05
//------------------------//------------------------
#include "Window.h"
#include "Game.h"


//----------------------------------------------------------------------
//! @brief ���C���\�[�X
//!
//! @param �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	//COM���C�u����������������B
	if (FAILED(CoInitializeEx(nullptr, COINITBASE_MULTITHREADED)))
		return 1;

	int width = 800;
	int height = 600;

	//Game�I�u�W�F�N�g�̐���
	Game game(width, height);
	//�Q�[���̎��s������
	MSG msg = game.Tick();

	//COM�C�j�V�����C�Y�̏I������(���)
	CoUninitialize();
	return (int)msg.wParam;

}