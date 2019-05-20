//---------------------------------------------
//作成者	: 寺本 啓志
//最終更新日: 2018 06/27
//中身	:	  GameScore(リザルトのスコア表示)のCpp
//内容	:	　GameScore(リザルトのスコア表示)のタスク
//--------------------------------------------

//#include "../../pch.h"
#include "GameScore.h"
#include "../../GameSystem/GameSabe.h"

using namespace MyGame;

/// <summary>
/// コンストラクタ
/// </summary>
GameScore::GameScore()
{
	m_score = 0;
}


/// <summary>
/// デストラクタ
/// </summary>
GameScore::~GameScore()
{
	//何もしない
}


/// <summary>
/// 初期化
/// </summary>
void GameScore::Initilize()
{
	//テクスチャの読み込み
	for (int i = 0; i < 5; i++)
	{
		//スコアの場所のセット
		m_DrawData[i].SetPos(400.0f - (i * 96), 530.0f);
		//テクスチャの読み込み
		System::DrawManager::GetInstance().LoadTexture(m_DrawData[i], L"Resources\\GameScene\\Number.png");
	}
	//スコアの設定
	m_score = System::GameSabe::GetInstance().GetData();
}


/// <summary>
/// 更新
/// </summary>
void GameScore::Update()
{
	//代入
	int n = this->m_score;
	//文字の列表示
	for (int i = 0; i < 5; i++)
	{
		int number;
		number = n % 10;
		n = n / 10;
		int leftX = 0 + (64 * (number % 4));
		int topY = 0 + (64 * (number / 4));
		//切り取りの設定
		m_DrawData[i].SetRect(leftX, topY, leftX + 64, topY + 64);
	}

}

/// <summary>
/// 描画
/// </summary>
void GameScore::Draw()
{
	for (int i = 0; i < 5; i++)
	{
		//描画
		System::DrawManager::GetInstance().Draw(m_DrawData[i]);
	}
}
