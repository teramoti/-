//---------------------------------------------
//作成者	: 寺本 啓志
//最終更新日: 2018 06/13
//中身	:	  TitlLogo(タイトル名)のCpp
//内容	:	　TitlLogo(タイトル名)のタスク
//--------------------------------------------


#include "GameReadyWord.h"

using namespace DirectX;

using namespace DirectX::SimpleMath;
/// <summary>
/// コンストラクタ
/// </summary>
GameReadyWord::GameReadyWord() : m_data() , m_Pos(Vector2(400, 200))
{
	//何もしない
}

/// <summary>
/// デストラクタ
/// </summary>
GameReadyWord::~GameReadyWord()
{

}
/// <summary>
/// 開始処理
/// </summary>
void GameReadyWord::Initilize()
{
	// テクスチャのロード
	System::DrawManager::GetInstance().LoadTexture(m_data, L"Resources\\Textures\\Ready.png");

	m_data.SetPos(m_Pos);
	m_data.SetScale(Vector2(2, 2));
	m_data.SetRect(0, 0, 150,60);
	m_data.SetOrigin(static_cast<float>(m_data.GetRect().right), static_cast<float>(m_data.GetRect().bottom));
}

void GameReadyWord::Update()
{
	
}

void GameReadyWord::Draw()
{
	System::DrawManager::GetInstance().Draw(m_data);

}