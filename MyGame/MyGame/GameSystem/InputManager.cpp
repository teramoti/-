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