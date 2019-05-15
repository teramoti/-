//---------------------------------------------
//作成者	: 寺本 啓志
//最終更新日: 2018 06/27
//中身	:	TitletKeyDown(リザルトのスコア表示)のヘッダー
//内容	:	TitletKeyDown(リザルトのスコア表示)のタスク
//--------------------------------------------

#pragma once
#include <d3d11.h>
#include <SimpleMath.h>
#include "../../GameSystem/DrawManager.h"

class TitleKeyDown
{

public:

	//リザルトスコアのコンストラクタ
	TitleKeyDown();
	//リザルトスコアのデストラクタ
	~TitleKeyDown();

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
	System::DrawData m_data;
	//スコア受け取り
	int m_frame;
	bool m_Frash;


};
