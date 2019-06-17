#include "ResultRecord.h"

ResultRecord::ResultRecord() : m_FlamNum(0) , m_Flag(true)
{
}

ResultRecord::~ResultRecord()
{
}

void ResultRecord::Initilize()
{
	m_data.SetPos(0, 300);
	m_data.SetRect(0, 0, 200,64);
	m_data.SetOrigin(0, 0);
	System::DrawManager::GetInstance().LoadTexture(m_data, L"Resources\\Textures\\NewRecord.png");
}

void ResultRecord::Update()
{
	m_FlamNum++;

	if (m_FlamNum > 60)
	{
		m_Flag = !m_Flag;
		m_FlamNum = 0;
	}
}

void ResultRecord::Render()
{
	if (m_Flag == true)
	{
		System::DrawManager::GetInstance().Draw(m_data);

	}
}