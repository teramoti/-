//------------------------//------------------------
// Contents(�������e) dx.h�̓��e������
//------------------------//------------------------
// user(�쐬��) Keishi Teramoto
// Created date(�쐬��) 2018 / 07 / 13
// last updated (�ŏI�X�V��) 2018 / 11 / 05
//------------------------//------------------------
#pragma once

#include <windows.h>
#include <stdexcept>

namespace DX
{
	inline void ThrowIfFailed(HRESULT hr)
	{
		if (FAILED(hr))
		{
			// DirectX API�G���[���擾���邽�߂��̍s�Ƀu���C�N�|�C���g��ݒ肷��
			throw std::exception();
		}
	}
}