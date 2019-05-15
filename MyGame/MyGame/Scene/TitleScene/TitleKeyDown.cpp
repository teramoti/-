//---------------------------------------------
//作成者	: 寺本 啓志
//最終更新日: 2018 06/27
//中身	:	  ResultScore(リザルトのスコア表示)のCpp
//内容	:	　ResultScore(リザルトのスコア表示)のタスク
//--------------------------------------------


#include "TitleKeyDown.h"
using namespace DirectX;
using namespace DirectX::SimpleMath;
/// <summary>
/// コンストラクタ
/// </summary>
TitleKeyDown::TitleKeyDown() :  m_frame(0), m_Frash(false), m_Pos(200, 500) , m_data()
{

}
/// <summary>
/// デストラクタ
/// </summary>
TitleKeyDown::~TitleKeyDown()
{

}

/// <summary>
/// 初期化
/// </summary>
void TitleKeyDown::Initilize()
{
	// テクスチャのロード
	System::DrawManager::GetInstance().LoadTexture(m_data, L"Resources\\Textures\\Space.png");
	m_Pos=Vector2(500, 450);
	m_data.SetPos(m_Pos);
	m_data.SetRect(0, 0, 150,90);
	m_data.SetOrigin(0, 0);
	m_data.SetScale(Vector2(2,2));

	
}
/// <summary>
/// 更新
/// </summary>

void TitleKeyDown::Update()
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
void TitleKeyDown::Draw()
{
	if (m_Frash == true)
	{
		System::DrawManager::GetInstance().Draw(m_data);
	}
}
