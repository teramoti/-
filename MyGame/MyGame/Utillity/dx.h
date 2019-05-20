#pragma once

#include <windows.h>
#include <stdexcept>

namespace DX
{
	inline void ThrowIfFailed(HRESULT hr)
	{
		if (FAILED(hr))
		{
			// DirectX APIエラーを取得するためこの行にブレイクポイントを設定する
			throw std::exception();
		}
	}
}