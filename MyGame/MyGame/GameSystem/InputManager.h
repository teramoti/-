#pragma once

//�C���N���[�h�t�@�C���̐錾
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

		// �L�[�{�[�h��Ԏ擾
		DirectX::Keyboard::State GetKeyboardState();

		// �L�[�{�[�h�g���b�J�[�擾
		DirectX::Keyboard::KeyboardStateTracker GetKeyboardTracker();


		// �X�V
		void Update(
					DirectX::Keyboard::State* lmpKeyboard,
					DirectX::Keyboard::KeyboardStateTracker* lmbKeyboadTracker);

	private:
		
		// �L�[�{�[�h
		DirectX::Keyboard::State*				 m_keyboard;

		// �L�[�{�[�h�g���b�J�[
		DirectX::Keyboard::KeyboardStateTracker* mbKeyboadTracker;
	};
}