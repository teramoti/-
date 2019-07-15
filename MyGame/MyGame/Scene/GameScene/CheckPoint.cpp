#include "CheckPoint.h"



CheckPoint::CheckPoint() : CheckBlock{false,false,false}, m_FinalFlag(false)
{
}

CheckPoint::~CheckPoint()
{
}

void CheckPoint::Initilize()
{
	m_box[0].Initialize();
	m_box[0].SetTrans(DirectX::SimpleMath::Vector3(0, -3, 0));
	m_box[0].SetSize(DirectX::SimpleMath::Vector3(96, 100.5f, 96));
	//CheckPoint1ÇÃê›íË
	m_box[1].Initialize();	
	m_box[1].SetTrans(DirectX::SimpleMath::Vector3(500,-3, 500));
	m_box[1].SetSize(DirectX::SimpleMath::Vector3(96, 100.5f, 96));

	//CheckPoint2ÇÃê›íË

	m_box[2].Initialize();
	m_box[2].SetTrans(DirectX::SimpleMath::Vector3(500, -3, -500));
	m_box[2].SetSize(DirectX::SimpleMath::Vector3(96, 100.5f, 96));

	for (int i = 0; i < 3; i++)
	{	
		m_box[i].SetPointPos();
	}

	m_directX11.Get().GetEffect()->SetDirectory(L"Resources\\Model");

}

void CheckPoint::Update()
{
	for (int i = 0; i < 3; i++)
	{
		m_box[i].Update();
	}
	Teramoto::Object3D::Update();

}

void CheckPoint::Render(DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj)
{
	for (int i = 0; i < 3; i++)
	{
		m_box[i].Render(view,proj);
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
