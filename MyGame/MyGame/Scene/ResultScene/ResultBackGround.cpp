#include "ResultBackGround.h"



ResultBackGround::ResultBackGround()
{
}

ResultBackGround::~ResultBackGround()
{
}

void ResultBackGround::Initilize()
{
	m_data.SetPos(0, 0);
	m_data.SetRect(0, 0, 800, 600);
	m_data.SetOrigin(0,0);
	System::DrawManager::GetInstance().LoadTexture(m_data, L"Resources\\Textures\\TitleBack.png");
}

void ResultBackGround::Update()
{
}

void ResultBackGround::Render()
{
	System::DrawManager::GetInstance().Draw(m_data);

}
