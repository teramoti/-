//------------------------//------------------------
// Contents(処理内容) Math.cppの内容を書く
//------------------------//------------------------
// user(作成者) Keishi Teramoto
// Created date(作成日) 2018 / 07 / 07
// last updated (最終更新日) 2018 / 07 / 07
//------------------------//------------------------
// ヘッダファイルの読み込み ================================================

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Math.h"

using namespace std;
using namespace Teramoto;

// π
const float Teramoto::Math::PI = 3.14159274f;

/// <summary>
/// 絶対値を返す
/// </summary>
/// <param name="num">数値</param>
/// <returns>絶対値</returns>
template<typename T>
T Teramoto::Math::Abs(T num)
{
	if (num < 0)
	{
		num *= -1;
	}
	return num;
}

/// <summary>
/// 2点の距離を求める
/// <summary>
/// <param name="p1">点1</param>
/// <param name="p2">点2</param>
/// <returns>距離</returns>
template<typename T>
inline T Math::Difference(T p1, T p2)
{
	auto length = p1 - p2;
	return Abs<T>(length);
}

/// <summary>
/// 自分からターゲットへの方向(角度)を求める
/// </summary>
/// <param name="myPos1">2D(自分の座標X)or3D(自分の座標Z)</param>
/// <param name="myPos2">2D(自分の座標Y)or3D(自分の座標X)</param>
/// <param name="targetPos1">2D(対象の座標X)or3D(対象の座標Z)</param>
/// <param name="targetPos2">2D(対象の座標Y)or3D(対象の座標X)</param>
/// <returns>対象物への角度</returns>
float Teramoto::Math::TargetAngle(float myPos1, float myPos2, float targetPos1, float targetPos2)
{
	float dPos1;
	float dPos2;
	float angle;

	dPos1 = myPos1 - targetPos1;
	dPos2 = myPos2 - targetPos2;

	angle = float(atan2(dPos2, dPos1));

	return angle;	
}
	

template<typename T>
bool Teramoto::Math::Clamp(T value, T num1, T num2)
{
	if (num1 < num2)
	{
		if (value > num2) return false;
		if (value < num1) return false;

		return true;
	}

	if (num1 > num2)
	{
		if (value < num2) return false;
		if (value > num1) return false;

		return true;
	}

	return true;
}
//bool MyLibrary::Math::Clamp(T value, T lo, T hi)
//{
//	if(value < hi)  return false;
//	if(value > lo)	return false;
//
//	return true;
//}

/// <summary>
/// 乱数の取得(int型)
/// </summary>
/// <param name="min">最小値</param>
/// <param name="max">最大値</param>
/// <returns>minからmaxの間の値</returns>
int Teramoto::Math::GetRand(int min, int max)
{
	int random;

	srand((unsigned)time(NULL));
	random = rand() % (max - min + 1) + min;

	return random;
}

/// <summary>
/// デグリーをラジアンに変換
/// </summary>
/// <param name="deg">デグリー角</param>
/// <returns>ラジアン角</returns>
float Teramoto::Math::ToRad(float deg)
{
	return deg * (PI / 180.f);
}

/// <summary>
/// ラジアンをデグリーに変換
/// </summary>
/// <param name="rad">ラジアン角</param>
/// <returns>デグリー角</returns>
float Teramoto::Math::ToDeg(float rad)
{
	return rad * (180.f * PI);
}
