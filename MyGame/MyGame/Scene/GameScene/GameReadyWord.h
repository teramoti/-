//---------------------------------------------
//作成者	: 寺本 啓志
//最終更新日: 2018 06/13
//中身	:	  GameReadyWord(タイトル名)のヘッダー
//内容	:	　GameReadyWord(タイトル名)のタスク管理
//--------------------------------------------

#pragma once
#include <d3d11.h>
#include <SimpleMath.h>
#include "../../GameSystem/DrawManager.h"
class GameReadyWord
{
public:

	//タイトル名のコンストラクタ
	GameReadyWord();
	//タイトル名のデストラクタ
	~GameReadyWord();

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
