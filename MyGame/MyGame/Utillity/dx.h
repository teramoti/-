//------------------------//------------------------
// Contents(処理内容) dx.hの内容を書く
//------------------------//------------------------
// user(作成者) Keishi Teramoto
// Created date(作成日) 2018 / 07 / 13
// last updated (最終更新日) 2018 / 11 / 05
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
			// DirectX APIエラーを取得するためこの行にブレイクポイントを設定する
			throw std::exception();
		}
	}
}