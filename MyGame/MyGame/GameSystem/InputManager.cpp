//------------------------//------------------------
// Contents(�������e) InputManager.cpp�̓��e������
//------------------------//------------------------
// user(�쐬��) Keishi Teramoto
// Created date(�쐬��) 2018 / 07 / 13
// last updated (�ŏI�X�V��) 2018 / 07 / 13
//------------------------//------------------------


//�C���N���[�h�t�@�C���̐錾
#include "InputManager.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
System::InputManager::InputManager()
{
}

DirectX::Keyboard::State System::InputManager::GetKeyboardState()
{
	return *m_keyboard;
}

DirectX::Keyboard::KeyboardStateTracker System::InputManager::GetKeyboardTracker()
{
	return *mbKeyboadTracker;
}

System::InputManager::~InputManager()
{
	
}

/// <summary>
/// �X�V����
/// </summary>
void System::InputManager::Update(
								  DirectX::Keyboard::State* lmpKeyboard,
								  DirectX::Keyboard::KeyboardStateTracker* lmbKeyboadTracker)
{
	mbKeyboadTracker = lmbKeyboadTracker;
	m_keyboard = lmpKeyboard;
}