//---------------------------------------------
//作成者	: 寺本 啓志
//最終更新日: 2018 06/13
//中身	:	  TitlLogo(タイトル名)のCpp
//内容	:	　TitlLogo(タイトル名)のタスク
//--------------------------------------------
#include <d3d11.h>
#include <SimpleMath.h>
#include "TitleBackGround.h"
using namespace DirectX;

using namespace DirectX::SimpleMath;
/// <summary>
/// コンストラクタ
/// </summary>
TitleBackGround::TitleBackGround() : m_data() , m_Pos(Vector2(0,0))
{
	//何もしない
}

/// <summary>
/// デストラクタ
/// </summary>
TitleBackGround::~TitleBackGround()
{

}
/// <summary>
/// 開始処理
/// </summary>
void TitleBackGround::Initilize()
{
	// テクスチャのロード
	System::DrawManager::GetInstance().LoadTexture(m_data, L"Resources\\Textures\\TitleBack.png");

	m_data.SetPos(0, 0);
	m_data.SetRect(0, 0, 800,600);
	m_data.SetScale(5, 5);
	m_data.SetOrigin(400,300);
}

void TitleBackGround::Update()
{
	
}

void TitleBackGround::Draw()
{
	System::DrawManager::GetInstance().Draw(m_data);

}