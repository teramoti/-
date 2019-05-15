#include "ResultRank.h"
#include "../../GameSystem/GameSaveData.h"

ResultRank::ResultRank()
{
}

ResultRank::~ResultRank()
{
}

void ResultRank::Initilize()
{
	m_num = GameSaveData::GetInstance().GetRank();
		System::DrawManager::GetInstance().LoadTexture(m_DrawData, L"Resources\\Textures\\RANK.png");

	switch (m_num)
	{
	case 1:
		m_DrawData.SetRect(0, 0, 128, 128);
		break;
	case 2:

		m_DrawData.SetRect(128, 0, 256, 128);

		break;

	default:

		m_DrawData.SetRect(0, 0, 0,0);
		break;
	}

	m_DrawData.SetPos(100, 400);
	m_DrawData.SetOrigin(0, 0);

}

void ResultRank::Update()
{
}

void ResultRank::Draw()
{
	System::DrawManager::GetInstance().Draw(m_DrawData);
}
