//---------------------------------------------
//作成者	: 寺本 啓志
//最終更新日: 2018 06/13
//中身	:	  TitleStarEffect(タイトル名)のヘッダー
//内容	:	　TitleStarEffect(タイトル名)のタスク管理
//--------------------------------------------

#pragma once
#include <d3d11.h>
#include <SimpleMath.h>
#include "../../GameSystem/DrawManager.h"
class TitleStarEffect
{
public:

	//タイトル名のコンストラクタ
	TitleStarEffect();
	//タイトル名のデストラクタ
	~TitleStarEffect();
public:
	//初期化処理
	void Initilize();
	//更新処理
	void Update();

	//描画処理
	void Draw();
	void Move();
private:

	//タイトルロゴのポジション
	DirectX::SimpleMath::Vector2 m_Pos;
	DirectX::SimpleMath::Vector2 m_Speed;
	System::DrawData m_data;
};
