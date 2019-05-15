//---------------------------------------------
//作成者	: 寺本 啓志
//最終更新日: 2018 06/27
//中身	:	  ResultScore(リザルトのスコア表示)のCpp
//内容	:	　ResultScore(リザルトのスコア表示)のタスク
//--------------------------------------------


#include "ResultKeyDown.h"

/// <summary>
/// コンストラクタ
/// </summary>
ResultKeyDown::ResultKeyDown() :  m_frame(0), m_Frash(false)
{

}
/// <summary>
/// デストラクタ
/// </summary>
ResultKeyDown::~ResultKeyDown()
{

}

/// <summary>
/// 初期化
/// </summary>
void ResultKeyDown::Initilize()
{
	// テクスチャのロード
	System::DrawManager::GetInstance().LoadTexture(m_DrawData, L"Resources\\Textures\\Zkey.png");

	m_DrawData.SetPos(400, 400);
	m_DrawData.SetRect(0, 0, 150,90);
	m_DrawData.SetOrigin(0, 0);
	m_DrawData.SetScale(DirectX::SimpleMath::Vector2(2, 2));

}
/// <summary>
/// 更新
/// </summary>

void ResultKeyDown::Update()
{
	m_frame++;

	if (m_frame > 60)
	{
		m_frame = 0;
		m_Frash = !m_Frash;
	}
}

/// <summary>
/// 描画
/// </summary>
void ResultKeyDown::Draw()
{
	if (m_Frash == true)
	{
		System::DrawManager::GetInstance().Draw(m_DrawData);
	}
}
