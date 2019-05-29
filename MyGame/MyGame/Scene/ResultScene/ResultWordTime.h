//---------------------------------------------
//作成者	: 寺本 啓志
//最終更新日: 2018 06/27
//中身	:	  ResultTime(リザルトの文字)のヘッダー
//内容	:	　ResultTime(リザルトの文字)のタスク
//--------------------------------------------

#pragma once


#include "../../GameSystem/DrawManager.h"

class ResultWordTime
{
public:

	//リザルト文字のコンストラクタ
	ResultWordTime();
	//リザルト文字のデストラクタ
	~ResultWordTime();

public:
	//始まる処理
	void Initilize();
	//更新処理
	void Update();
	//描画処理
	void Draw();

	//タイトルロゴのポジション
	DirectX::SimpleMath::Vector2 m_Pos;
	//描画用の変数
	System::DrawData m_drawData;
};
