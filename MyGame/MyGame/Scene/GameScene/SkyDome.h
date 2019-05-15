//----------------------------------------
/// <summary>
/// コースのクラス
/// GS2 寺本 啓志
/// </summary>
//----------------------------------------
#pragma once
#include <d3d11.h>
#include <SimpleMath.h>
#include "../../GameSystem/Object.h"

class SkyDome : public MyLib::Object3D
{
public:
	const float SKYDOME_ROTATION_Y = 0.005f;
public:
	SkyDome();
	~SkyDome();
public:

	void Initilize();
	void Update();
	void ReUpdate();
	void Render();
};