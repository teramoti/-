#include "ResultTimeComma.h"

ResultTimeComma::ResultTimeComma()
{
}

ResultTimeComma::~ResultTimeComma()
{
}

void ResultTimeComma::Initilize()
{
	System::DrawManager::GetInstance().LoadTexture(m_DrawData, L"Resources\\Textures\\konnma.png");
}

void ResultTimeComma::Update()
{
}

void ResultTimeComma::Draw()
{
	m_DrawData.SetPos(m_Pos);
	m_DrawData.SetRect(0,0,64,64);
	m_DrawData.SetOrigin(0, 0);
	m_DrawData.SetScale(0.5f, 0.5f);
	System::DrawManager::GetInstance().Draw(m_DrawData);
}
