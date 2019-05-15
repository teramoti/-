//---------------------------------------------
//作成者	: 寺本 啓志
//最終更新日: 2018 06/13
//中身	:	  TitlLogo(タイトル名)のCpp
//内容	:	　TitlLogo(タイトル名)のタスク
//--------------------------------------------
#include "TitleStarEffect.h"

using namespace DirectX;

using namespace DirectX::SimpleMath;
/// <summary>
/// コンストラクタ
/// </summary>
TitleStarEffect::TitleStarEffect() :m_Pos(-64,-64), m_Speed(5,5)  ,m_data()
{
	//何もしない
}

/// <summary>
/// デストラクタ
/// </summary>
TitleStarEffect::~TitleStarEffect()
{
	//何もしない
}
/// <summary>
/// 開始処理
/// </summary>
void TitleStarEffect::Initilize()
{
	// テクスチャのロード									 
	System::DrawManager::GetInstance().LoadTexture(m_data, L"Resources\\Textures\\Star.png");
	m_data.SetRect(0, 0, 64,64);
	m_data.SetPos(m_Pos.x,m_Pos.y);
	m_data.SetOrigin(0, 0);
}

void TitleStarEffect::Update()
{
	Move();
	if (m_Pos.y > 664)
	{	
		m_Pos.y = -64;
		
	}
	if (m_Pos.x > 864)
	{
		m_Pos.x = -64;
	}

}

void TitleStarEffect::Draw()
{
	System::DrawManager::GetInstance().Draw(m_data);

}

void TitleStarEffect::Move()
{
	m_Pos += m_Speed;

	m_data.SetPos(m_Pos);
}
