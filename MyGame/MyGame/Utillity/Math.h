//------------------------//------------------------
// Contents(処理内容) math.hの内容を書く
//------------------------//------------------------
// user(作成者) Keishi Teramoto
// Created date(作成日) 2018 / 07 / 06
// last updated (最終更新日) 2018 / 07 / 06
//------------------------//------------------------
// 多重インクルードの防止 ==================================================
#pragma once

// ヘッダファイルの読み込み ================================================
#include <math.h>


/// <summary>
//!
//! @brief Mathクラス
//!
/// </summary>
namespace MyLibrary
{
	class Math
	{
	private:
		// 円周率
		static const float PI;

	public:
		// 絶対値を求める
		template<typename T>
		static T Abs(T num);

		// 二つの点の差分を求める
		template<typename T>
		static T Difference(T p1, T p2);

		// 自分からターゲットへの方向(角度)を求める
		static float TargetAngle(float myPos1, float myPos2, float targetPos1, float targetPos2);

		// クランプ関数
		template<typename T>
		static bool Clamp(T value, T num1, T num2);


		// 乱数
		static int GetRand(int min, int max);

		// デグリーをラジアンに変換
		static float ToRad(float deg);

		// ラジアンをデグリーに変換
		static float ToDeg(float rad);
	
	};

}

