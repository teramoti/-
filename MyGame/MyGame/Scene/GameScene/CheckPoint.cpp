#include "CheckPoint.h"
using namespace DirectX;
using namespace DirectX::SimpleMath;

CheckPoint::CheckPoint() 
{
}

CheckPoint::~CheckPoint()
{
}

void CheckPoint::Initilize()
{
	m_box[0].Initialize();
	m_box[0].SetTrans(Vector3(0, -3, 0));
	m_box[0].SetSize(Vector3(230, 16.5f, 230));
	//CheckPoint1ÇÃê›íË
	m_box[1].Initialize();	
	m_box[1].SetTrans(Vector3(-290,-3, 500));

	m_box[1].SetSize(Vector3(230, 16.5f, 230));
	//CheckPoint2ÇÃê›íË
	m_box[2].Initialize();
	m_box[2].SetTrans(Vector3(-280, -3, -520));
	m_box[2].SetSize(Vector3(230, 16.5f, 230));

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
	MyLib::Object3D::Draw();

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
