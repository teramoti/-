//---------------------------------------------
//作成者	: 寺本 啓志
//最終更新日: 2018 06/27
//中身	:	  ResultTime(リザルトの文字)のCpp
//内容	:	　ResultTime(リザルトの文字)のタスク
//--------------------------------------------

#include "ResultTime.h"
#include "../../GameSystem/GameSaveData.h"

/// <summary>
/// コンストラクタ
/// </summary>
ResultTime::ResultTime() : m_score(0)
{
	//何もしない
}

/// <summary>
/// デストラクタ
/// </summary>
ResultTime::~ResultTime()
{
	//何もしない
	
	m_Comma;
}

/// <summary>
/// 開始処理
/// </summary>
void ResultTime::Initilize()
{

	m_num = GameSaveData::GetInstance().GetStage();
	switch (m_num)
	{
	case 1:
		//スコアの設定
		m_score = GameSaveData::GetInstance().GetGoal1Time();
	default:
		break;
	}



	//テクスチャの読み込み
	for (int i = 0; i < 4; i++)
	{
		System::DrawManager::GetInstance().LoadTexture(m_DrawData[i], L"Resources\\Textures\\Number.png");
	}

	m_Comma = new ResultTimeComma();
	m_Comma->SetPos(DirectX::SimpleMath::Vector2(310, 200));

	m_Comma->Initilize();
}

/// <summary>
/// 更新処理
/// </summary>
void ResultTime::Update()
{


}

/// <summary>
/// 描画処理
/// </summary>
void ResultTime::Draw()
{
	m_rect[0] = { 0 + (((int)m_score / 1000 % 10) * 50),0,50 + (((int)m_score / 1000 % 10) * 50),50 };
	m_rect[1] = { 0 + (((int)m_score / 100 % 10) * 50),0,50 + (((int)m_score / 100 % 10) * 50),50 };
	m_rect[2] = { 0 + (((int)m_score / 10 % 10) * 50),0,50 + (((int)m_score / 10 % 10) * 50),50 };
	m_rect[3] = { 0 + (((int)m_score % 10) * 50),0,50 + (((int)m_score % 10) * 50),50 };

	for (int i = 0; i < 4; i++)
	{
		m_DrawData[i].SetPos(200.0f + (i * 60), 200.0f);
		m_DrawData[i].SetRect(m_rect[i].left, m_rect[i].top, m_rect[i].right, m_rect[i].bottom);
		m_DrawData[i].SetOrigin(0, 0);
		System::DrawManager::GetInstance().Draw(m_DrawData[i]);
	}
	m_Comma->Draw();
}
