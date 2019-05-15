//---------------------------------------------
//作成者	: 寺本 啓志
//最終更新日: 2018 06/27
//中身	:	  ResultWordTime(リザルトの文字)のCpp
//内容	:	　ResultWordTime(リザルトの文字)のタスク
//--------------------------------------------

#include "../../GameSystem/GameSabe.h"

#include "ResultWordTime.h"


/// <summary>
/// コンストラクタ
/// </summary>
ResultWordTime::ResultWordTime()
{
	//何もしない
}

/// <summary>
/// デストラクタ
/// </summary>
ResultWordTime::~ResultWordTime()
{
	//何もしない
}

/// <summary>
/// 開始処理
/// </summary>
void ResultWordTime::Initilize()
{
	m_DrawData.SetPos(0,90);
	m_DrawData.SetRect(0, 0, 200, 90);
	m_DrawData.SetOrigin(0, 0);
	System::DrawManager::GetInstance().LoadTexture(m_DrawData, L"Resources\\Textures\\Time.png");
}

/// <summary>
/// 更新処理
/// </summary>
void ResultWordTime::Update()
{
}

/// <summary>
/// 描画処理
/// </summary>
void ResultWordTime::Draw()
{
	System::DrawManager::GetInstance().Draw(m_DrawData);
}
