
//---------------------------------------------
//作成者	: 寺本 啓志
//最終更新日: 2018 06/13
//中身	:	  TitlLogo(タイトル名)のCpp
//内容	:	　TitlLogo(タイトル名)のタスク
//--------------------------------------------

#include <d3d11.h>
#include <SimpleMath.h>
#include <Keyboard.h>
#include "../../GameSystem/InputManager.h"
#include "TitleAroow.h"




/// <summary>
/// コンストラクタ
/// </summary>
TitleAroow::TitleAroow() : m_data()
{
	//何もしない
}

/// <summary>
/// デストラクタ
/// </summary>
TitleAroow::~TitleAroow()
{
}
/// <summary>
/// 開始処理
/// </summary>
void TitleAroow::Initilize()
{
	// テクスチャのロード
	System::DrawManager::GetInstance().LoadTexture(m_data, L"Resources\\Textures\\Arrow.png");
	m_Pos = DirectX::SimpleMath::Vector2(150, 300);
	m_data.SetPos(m_Pos);
	m_data.SetOrigin(45, 45);
	m_data.SetRect(0,0,90,90);
	m_num = 0;
	//m_adx2le = MyLibrary::ADX2Le::GetInstance();

	// サウンドの読み込み
	//m_adx2le->//LoadAcb(L"TitleScene.acb", L"TitleScene.awb");

}

void TitleAroow::Update(int& num)
{	
	//m_adx2le->Stop(0);

	if (System::InputManager::GetInstance().GetKeyboardTracker().pressed.Up)
	{
		m_Pos.y = 300;
		m_num = 0;
		//if (!m_adx2le->IsPlayStateByID(m_criAtomExPlaybackId))
		//{
		//	// 効果音の再生
		//	m_criAtomExPlaybackId = m_adx2le->Play(0);
		//}
	}
	if (System::InputManager::GetInstance().GetKeyboardTracker().pressed.Down)
	{	
		m_Pos.y = 400;
		m_num = 1;
		//if (!m_adx2le->IsPlayStateByID(m_criAtomExPlaybackId))
		//{
		//	// 効果音の再生
		//	m_criAtomExPlaybackId = m_adx2le->Play(0);

		//}
	}
	num = m_num ;

	m_data.SetPos(m_Pos);
}

void TitleAroow::Draw()
{
	System::DrawManager::GetInstance().Draw(m_data);

}