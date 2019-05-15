//---------------------------------------------
//作成者	: 寺本 啓志
//最終更新日: 2018 06/13
//中身	:	  TitlLogo(タイトル名)のCpp
//内容	:	　TitlLogo(タイトル名)のタスク
//--------------------------------------------
#include "TitleGoGame.h"

using namespace DirectX;

using namespace DirectX::SimpleMath;
/// <summary>
/// コンストラクタ
/// </summary>
TitleGoGame::TitleGoGame()  :m_data() , m_Pos(0,0)
{
	//何もしない
}

/// <summary>
/// デストラクタ
/// </summary>
TitleGoGame::~TitleGoGame()
{
	//何もしない
}
/// <summary>
/// 開始処理
/// </summary>
void TitleGoGame::Initilize()
{// テクスチャのロード
	System::DrawManager::GetInstance().LoadTexture(m_data, L"Resources\\Textures\\GoGame.png");
	m_data.SetRect(0, 0, 200, 90);
	m_Pos = Vector2(300, 250);
	m_data.SetPos(m_Pos);
	m_data.SetOrigin(0, 0);
	
}

void TitleGoGame::Update()
{
	
}

void TitleGoGame::Draw()
{
 	System::DrawManager::GetInstance().Draw(m_data);

}