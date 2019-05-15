#include <d3d11.h>
#include <SimpleMath.h>
#include "CountDown.h"

CountDown::CountDown() : m_Pos(400,50)
{
}

CountDown::~CountDown()
{
	delete m_ready;
}

void CountDown::Initilize()
{
	System::DrawManager::GetInstance().LoadTexture(m_data,L"Resources\\Textures\\count.png");
	m_data.SetPos(m_Pos);

	m_data.SetOrigin(0,0);
	m_ready = new GameReadyWord();
	m_ready->Initilize();

}

void CountDown::Update()
{
	m_Count--;

}

void CountDown::Draw()
{	
	m_rect = { ((int)(m_Count / 60) * 150),0,150 + ((int)(m_Count / 60) * 150) ,150 };

	m_data.SetRect(m_rect.left, m_rect.top, m_rect.right, m_rect.bottom);

	if (m_Count > 0)

	{
		m_ready->Draw();

		System::DrawManager::GetInstance().Draw(m_data);
	}
}
