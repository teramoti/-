//------------------------//------------------------
// Contents(処理内容) InputManager.cppの内容を書く
//------------------------//------------------------
// user(作成者) Keishi Teramoto
// Created date(作成日) 2018 / 07 / 13
// last updated (最終更新日) 2018 / 07 / 13
//------------------------//------------------------


//インクルードファイルの宣言
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