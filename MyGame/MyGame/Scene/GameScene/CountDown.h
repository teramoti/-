//---------------------------------------------
//作成者	: 寺本 啓志
//最終更新日: 2018 06/13
//中身	:	 CountDownのヘッダー
//内容	:	CountDownのタスク管理
//--------------------------------------------

#pragma once
#include "../../GameSystem/DrawManager.h"
#include"GameReadyWord.h"
class CountDown
{
public:

	//タイトル名のコンストラクタ
	CountDown();
	//タイトル名のデストラクタ
	~CountDown();

public:
	//初期化処理
	void Initilize();
	//更新処理
	void Update();
	//描画処理
	void Draw();

	void SetTime(float& count)
	{
	 m_Count= count;
	}
private:

	//タイトルロゴのポジション
	DirectX::SimpleMath::Vector2 m_Pos;
	System::DrawData m_data;
	float m_Count;

	RECT m_rect;

	GameReadyWord* m_ready;
};
