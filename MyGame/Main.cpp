//
// Main.cpp
//

#include "Window.h"
#include "Game.h"


// Entry point
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