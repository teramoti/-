//---------------------------------------------
//作成者	: 寺本 啓志
//最終更新日: 2018 06/27
//中身	:	  ResultTime(リザルトの文字)のヘッダー
//内容	:	　ResultTime(リザルトの文字)のタスク
//--------------------------------------------

#pragma once

#include <d3d11_1.h>
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include <CommonStates.h>
#include "../../GameSystem/DrawManager.h"
#include "ResultTimeComma.h"
#include "ResultRecord.h"

class ResultHighTime
{
public:

	//リザルト文字のコンストラクタ
	ResultHighTime();
	//リザルト文字のデストラクタ
	~ResultHighTime();

public:
	//初期化処理
	void Initilize();
	//更新処理
	void Update();
	//描画処理
	void Draw();

	//タイトルロゴのポジション
	DirectX::SimpleMath::Vector2 m_Pos;
	//描画用の変数
	System::DrawData m_DrawData[4];
	//スコア受け取り
	float m_score;
	RECT m_rect[4];
	ResultTimeComma* m_Comma;
	ResultRecord* m_Record;
	int m_num;
};

