#include "TimeComma.h"

TimeComma::TimeComma()
{
}

TimeComma::~TimeComma()
{
}

void TimeComma::Initilize()
{
	System::DrawManager::GetInstance().LoadTexture(m_DrawData, L"Resources\\Textures\\konnma.png");
}

void TimeComma::Update()
{
}

void TimeComma::Draw()
{
	m_DrawData.SetPos(150,20);
	m_DrawData.SetRect(0,0,64,64);
	m_DrawData.SetOrigin(0, 0);
	m_DrawData.SetScale(0.5f, 0.5f);
	System::DrawManager::GetInstance().Draw(m_DrawData);
}
