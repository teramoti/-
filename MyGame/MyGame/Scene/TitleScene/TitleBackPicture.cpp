//---------------------------------------------
//作成者	: 寺本 啓志
//最終更新日: 2018 06/13
//中身	:	  TitlLogo(タイトル名)のCpp
//内容	:	　TitlLogo(タイトル名)のタスク
//--------------------------------------------
#include "TitleBackPicture.h"

using namespace DirectX;

using namespace DirectX::SimpleMath;
/// <summary>
/// コンストラクタ
/// </summary>
TitleBackPicture::TitleBackPicture()  :m_data() , m_Pos(0,0)
{
	//何もしない
}

/// <summary>
/// デストラクタ
/// </summary>
TitleBackPicture::~TitleBackPicture()
{
	//何もしない
}
/// <summary>
/// 開始処理
/// </summary>
void TitleBackPicture::Initilize()
{
	for (int i = 0; i < 2; i++)
	{
		// テクスチャのロード
		System::DrawManager::GetInstance().LoadTexture(m_data[i], L"Resources\\Textures\\Base.png");
		m_data[i].SetRect(0, 30, 500, 170);
		m_data[i].SetOrigin(0, 0);
	}
	m_Pos = Vector2(350, 250);

	m_data[0].SetPos(m_Pos);
	m_Pos = Vector2(400, 550);

	m_data[1].SetPos(m_Pos);
}

void TitleBackPicture::Update()
{
	
}

void TitleBackPicture::Draw()
{
	for (int i = 0; i < 2; i++)
	{
		System::DrawManager::GetInstance().Draw(m_data[i]);
	}

}