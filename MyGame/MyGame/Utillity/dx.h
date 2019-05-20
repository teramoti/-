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