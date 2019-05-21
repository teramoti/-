#pragma once

//インクルードファイルの宣言
#include <d3d11.h>
#include <SimpleMath.h>
#include <Mouse.h>
#include <KeyBoard.h>

#include "../Utillity/SingletonBase.h"
namespace System
{
	class InputManager : public Utility::SingletonBase<InputManager>
	{
	public:

		friend Utility::SingletonBase<InputManager>;

	private:

		InputManager();

		~InputManager();

	public:

		// キーボード状態取得
		DirectX::Keyboard::State GetKeyboardState();

		// キーボードトラッカー取得
		DirectX::Keyboard::KeyboardStateTracker GetKeyboardTracker();


		// 更新
		void Update(
					DirectX::Keyboard::State* lmpKeyboard,
					DirectX::Keyboard::KeyboardStateTracker* lmbKeyboadTracker);

	private:
		
		// キーボード
		DirectX::Keyboard::State*				 m_keyboard;

		// キーボードトラッカー
		DirectX::Keyboard::KeyboardStateTracker* mbKeyboadTracker;
	};
}