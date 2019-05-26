//---------------------------------------------
//作成者	: 寺本 啓志
//最終更新日: 2018 06/13
//中身	:	  TitlLogo(タイトル名)のCpp
//内容	:	　TitlLogo(タイトル名)のタスク
//--------------------------------------------
#include "../../GameSystem/DrawManager.h"
#include "TitleGoEnd.h"




/// <summary>
/// コンストラクタ
/// </summary>
TitleGoEnd::TitleGoEnd()  :m_data() , m_Pos(0,0)
{
	//何もしない
}

/// <summary>
/// デストラクタ
/// </summary>
TitleGoEnd::~TitleGoEnd()
{
	//何もしない
}
/// <summary>
/// 開始処理
/// </summary>
void TitleGoEnd::Initilize()
{	
	// テクスチャのロード
	System::DrawManager::GetInstance().LoadTexture(m_data, L"Resources\\Textures\\GoEnd.png");
	m_Pos = DirectX::SimpleMath::Vector2(300, 350);
	m_data.SetPos(m_Pos);
	m_data.SetRect(0, 0, 200,90);
	m_data.SetOrigin(0, 0);
}

void TitleGoEnd::Update()
{
	
}

void TitleGoEnd::Draw()
{
	System::DrawManager::GetInstance().Draw(m_data);

}