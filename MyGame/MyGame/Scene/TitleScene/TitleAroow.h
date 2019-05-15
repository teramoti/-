//---------------------------------------------
//作成者	: 寺本 啓志
//最終更新日: 2018 06/13
//中身	:	  TitleBackGround(タイトル名)のヘッダー
//内容	:	　TitleBackGround(タイトル名)のタスク管理
//--------------------------------------------

#pragma once
#include "../../GameSystem/DrawManager.h"
//#include "../..//ADX2/ADX2Le.h"

class TitleAroow
{
public:
	enum SERECT_ENUM
	{
		UP,
		DOWN,
		NONE

	};

public:

	
	//タイトル名のコンストラクタ
	TitleAroow();
	//タイトル名のデストラクタ
	~TitleAroow();

public:
	//始まる処理
	void Initilize();
	//更新処理
	void Update(int& num);
	//描画処理
	void Draw();

private:

	//タイトルロゴのポジション
	DirectX::SimpleMath::Vector2 m_Pos;
	System::DrawData m_data;

	int m_num;

	// サウンド
	//MyLibrary::ADX2Le* m_adx2le;

	// 音楽情報記憶用変数
	//CriAtomExPlaybackId m_criAtomExPlaybackId;
};
