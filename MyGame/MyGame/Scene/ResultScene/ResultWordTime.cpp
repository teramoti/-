//---------------------------------------------
//作成者	: 寺本 啓志
//最終更新日: 2018 06/27
//中身	:	  ResultWordTime(リザルトの文字)のCpp
//内容	:	　ResultWordTime(リザルトの文字)のタスク
//--------------------------------------------

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
	m_drawData.SetPos(0.0f,90.0f);
	m_drawData.SetRect(0.0f, 0.0f, 200.0f, 90.0f);
	m_drawData.SetOrigin(0.0f, 0.0f);

	System::DrawManager::GetInstance().LoadTexture(m_drawData, L"Resources\\Textures\\Time.png");
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
	System::DrawManager::GetInstance().Draw(m_drawData);
}
