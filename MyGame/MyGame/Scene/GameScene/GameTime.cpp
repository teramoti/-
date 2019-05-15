//---------------------------------------------
//作成者	: 寺本 啓志
//最終更新日: 2018 06/27
//中身	:	  GameTime(リザルトの文字)のCpp
//内容	:	　GameTime(リザルトの文字)のタスク
//--------------------------------------------

#include "GameTime.h"
/// <summary>
/// コンストラクタ
/// </summary>
GameTime::GameTime() : m_score(0)
{
	//何もしない
}

/// <summary>
/// デストラクタ
/// </summary>
GameTime::~GameTime()
{
	//何もしない
	delete  m_comma;

}

/// <summary>
/// 開始処理
/// </summary>
void GameTime::Initilize()
{
	//テクスチャの読み込み
	for (int i = 0; i < 4; i++)
	{
		System::DrawManager::GetInstance().LoadTexture(m_DrawData[i], L"Resources\\Textures\\Number.png");
	}

	m_comma = new TimeComma();
	m_comma->Initilize();
}

/// <summary>
/// 更新処理
/// </summary>
void GameTime::Update()
{


}

/// <summary>
/// 描画処理
/// </summary>
void GameTime::Draw(bool Flag)
{
	if (Flag == true)
	{
		m_rect[0] = { 0 + (((int)m_score / 1000 % 10) * 50),0,50 + (((int)m_score / 1000 % 10) * 50),50 };
		m_rect[1] = { 0 + (((int)m_score / 100 % 10) * 50),0,50 + (((int)m_score / 100 % 10) * 50),50 };
		m_rect[2] = { 0 + (((int)m_score / 10 % 10) * 50),0,50 + (((int)m_score / 10 % 10) * 50),50 };
		m_rect[3] = { 0 + (((int)m_score % 10) * 50),0,50 + (((int)m_score % 10) * 50),50 };

		for (int i = 0; i < 4; i++)
		{
			m_DrawData[i].SetPos(50.0f + (i * 55),30);
			m_DrawData[i].SetRect(m_rect[i].left, m_rect[i].top, m_rect[i].right, m_rect[i].bottom);
			m_DrawData[i].SetOrigin(0,0);
			System::DrawManager::GetInstance().Draw(m_DrawData[i]);
		}	
		m_comma->Draw();

	}

}
