#include "CheckPoint.h"



CheckPoint::CheckPoint() : CheckBlock{false,false,false}, m_FinalFlag(false)
{
}

CheckPoint::~CheckPoint()
{
	m_model.reset();
}

void CheckPoint::Initilize()
{
	m_directX11.Get().GetEffect()->SetDirectory(L"Resources\\Model");

}

void CheckPoint::Update()
{
	Teramoto::Object3D::Update();

}

void CheckPoint::Render(DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj)
{
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
