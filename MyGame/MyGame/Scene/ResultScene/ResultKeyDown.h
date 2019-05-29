//---------------------------------------------
//作成者	: 寺本 啓志
//最終更新日: 2018 06/27
//中身	:	 ResultKeyDown(リザルトのスコア表示)のヘッダー
//内容	:	ResultKeyDown(リザルトのスコア表示)のタスク
//--------------------------------------------

#pragma once
#include "../../GameSystem/DrawManager.h"

class ResultKeyDown
{

public:

	//リザルトスコアのコンストラクタ
	ResultKeyDown();
	//リザルトスコアのデストラクタ
	~ResultKeyDown();

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
	System::DrawData m_DrawData;
	//スコア受け取り
	int m_frame;
	bool m_Frash;
};
