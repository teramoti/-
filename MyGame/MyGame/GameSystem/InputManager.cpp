#include "InputManager.h"


/// <summary>
/// コンストラクタ
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
/// 更新処理
/// </summary>
void System::InputManager::Update(
								  DirectX::Keyboard::State* lmpKeyboard,
								  DirectX::Keyboard::KeyboardStateTracker* lmbKeyboadTracker)
{
	mbKeyboadTracker = lmbKeyboadTracker;
	m_keyboard = lmpKeyboard;
}