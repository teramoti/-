#include "CheckPoint.h"



CheckPoint::CheckPoint() 
{
}

CheckPoint::~CheckPoint()
{
}

void CheckPoint::Initilize()
{
	m_box[0].Initialize();
	m_box[0].SetTrans(DirectX::SimpleMath::Vector3(0, -3, 0));
	m_box[0].SetSize(DirectX::SimpleMath::Vector3(230, 16.5f, 230));
	//CheckPoint1‚ÌÝ’è
	m_box[1].Initialize();	
	m_box[1].SetTrans(DirectX::SimpleMath::Vector3(-290,-3, 500));

	m_box[1].SetSize(DirectX::SimpleMath::Vector3(230, 16.5f, 230));
	//CheckPoint2‚ÌÝ’è
	m_box[2].Initialize();
	m_box[2].SetTrans(DirectX::SimpleMath::Vector3(-280, -3, -520));
	m_box[2].SetSize(DirectX::SimpleMath::Vector3(230, 16.5f, 230));

	m_directX11.Get().GetEffect()->SetDirectory(L"Resources\\Model");

}

void CheckPoint::Update()
{
	for (int i = 0; i < 3; i++)
	{
		m_box[i].Update();
	}
	MyLib::Object3D::Update();

}

void CheckPoint::Render()
{
	for (int i = 0; i < 3; i++)
	{
		//m_box[i].Render();
	}
}

bool CheckPoint::Checkhit1(bool flag)
{
	CheckBlock[0] = flag;

	return flag;
}

bool CheckPoint::Checkhit2(bool flag)
{
	if (CheckBlock[0] == true)
	{
		CheckBlock[1] = flag;
		return flag;
	}
	return false;
}

bool CheckPoint::Checkhit3(bool flag)
{
	if (CheckBlock[1] == true)
	{
		CheckBlock[2] = flag;
		return flag;
	}
	return false;
}

bool CheckPoint::GetFlag()
{
	if (CheckBlock[2] == true)
	{
		m_FinalFlag = true;
	}
	return m_FinalFlag;
}
