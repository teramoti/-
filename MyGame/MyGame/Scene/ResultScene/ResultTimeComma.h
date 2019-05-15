//---------------------------------------------
//作成者	: 寺本 啓志
//最終更新日: 2018 06/27
//中身	:	  ResultTime(リザルトの文字)のヘッダー
//内容	:	　ResultTime(リザルトの文字)のタスク
//--------------------------------------------

#pragma once

#include <d3d11_1.h>
#include <SimpleMath.h>
#include "../../GameSystem/DrawManager.h"

class ResultTimeComma
{
public:

	//リザルト文字のコンストラクタ
	ResultTimeComma();
	//リザルト文字のデストラクタ
	~ResultTimeComma();

public:
	void SetPos(DirectX::SimpleMath::Vector2 pos)
	{
		m_Pos = pos;
	}
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
