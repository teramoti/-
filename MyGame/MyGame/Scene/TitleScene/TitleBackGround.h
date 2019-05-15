//---------------------------------------------
//作成者	: 寺本 啓志
//最終更新日: 2018 06/13
//中身	:	  TitleBackGround(タイトル名)のヘッダー
//内容	:	　TitleBackGround(タイトル名)のタスク管理
//--------------------------------------------

#pragma once

#include "../../GameSystem/DrawManager.h"
class TitleBackGround
{
public:

	//タイトル名のコンストラクタ
	TitleBackGround();
	//タイトル名のデストラクタ
	~TitleBackGround();

public:
	//始まる処理
	void Initilize();
	//更新処理
	void Update();
	//描画処理
	void Draw();

private:
	DirectX::SimpleMath::Vector2 m_Pos;
	System::DrawData m_data;
};
