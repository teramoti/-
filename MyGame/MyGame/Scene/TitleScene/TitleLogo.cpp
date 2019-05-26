//---------------------------------------------
//作成者	: 寺本 啓志
//最終更新日: 2018 06/13
//中身	:	  TitlLogo(タイトル名)のCpp
//内容	:	　TitlLogo(タイトル名)のタスク
//--------------------------------------------

#include "TitleLogo.h"




/// <summary>
/// コンストラクタ
/// </summary>
TitleLogo::TitleLogo() : m_data(), m_Pos(1000,150), m_Size(0.5,0.5)
{
	//何もしない
}

/// <summary>
/// デストラクタ
/// </summary>
TitleLogo::~TitleLogo()
{
	//何もしない
}
/// <summary>
/// 開始処理
/// </summary>
void TitleLogo::Initilize()
{	
	// テクスチャのロード
	System::DrawManager::GetInstance().LoadTexture(m_data, L"Resources\\Textures\\TitleLogo.png");

	m_data.SetPos(m_Pos);
	m_data.SetRect(0,0,600,120);
	m_data.SetScale(m_Size);
	m_data.SetOrigin(static_cast<float>(m_data.GetRect().right), static_cast<float>(m_data.GetRect().bottom));
}

void TitleLogo::Update()
{

	m_Pos.x -= 3.0f;

	if (m_Pos.x < 800)
	{
		m_Pos.x = 800;

	}
	m_Size.x += 0.05f;
	m_Size.y += 0.05f;

	if (m_Size.x >1.2)
	{
		m_Size.x = 1.2;
		m_Size.y = 1.2;
	}

	m_data.SetScale(m_Size);
	m_data.SetPos(m_Pos);
}

void TitleLogo::Draw()
{
	System::DrawManager::GetInstance().Draw(m_data);
}