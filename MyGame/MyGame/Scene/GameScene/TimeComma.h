//------------------------//------------------------
// Contents(処理内容) TimeComma.cppの内容を書く
//------------------------//------------------------
// user(作成者) Keishi Teramoto
// Created date(作成日) 2018 / 07 / 13
// last updated (最終更新日) 2018 / 11 / 05
//------------------------//------------------------
#pragma once

#include <d3d11_1.h>
#include <SimpleMath.h>
#include "../../GameSystem/DrawManager.h"

class TimeComma
{
public:

	//リザルト文字のコンストラクタ
	TimeComma();
	//リザルト文字のデストラクタ
	~TimeComma();

public:
	//始まる処理
	void Initilize();
	//更新処理
	void Update();
	//描画処理
	void Draw();
private:
	//タイトルロゴのポジション
	DirectX::SimpleMath::Vector2 m_Pos;
	//描画用の変数
	System::DrawData m_DrawData;
	RECT m_rect;
};
