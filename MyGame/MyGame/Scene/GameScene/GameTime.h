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
#include "TimeComma.h"

class GameTime
{
public:

	//リザルト文字のコンストラクタ
	GameTime();
	//リザルト文字のデストラクタ
	~GameTime();

public:
	//初期化処理
	void Initilize();
	//更新処理
	void Update();
	//描画処理
	void Draw(bool Flag);

	void SetTime(float score)
	{
		m_score= score;
	}
	void SetTime(int time)
	{
		m_time = time;
	}
private:
	//タイトルロゴのポジション
	DirectX::SimpleMath::Vector2 m_Pos;
	//描画用の変数
	System::DrawData m_DrawData[4];
	//スコア受け取り
	float m_score;
	int m_time;

	RECT m_rect[5];
	TimeComma* m_comma;
};
