//#include "../../../pch.h"
#include "Cource.h"



Cource::Cource()
{
}

Cource::~Cource()
{
}

void Cource::Initilize()
{
	m_directX11.Get().GetEffect()->SetDirectory(L"Resources\\Model");

	CreateResource();
	m_inBox.Initialize();
	m_inBox.SetTrans(DirectX::SimpleMath::Vector3(480, -15,0));
	m_inBox.SetSize(DirectX::SimpleMath::Vector3(290 ,30,300));

	m_inBox.SetPointPos();

	m_translation = DirectX::SimpleMath::Vector3(0, -1, 0);
}

void Cource::Update()
{
	m_inBox.Update();
	Object3D::Update();
}

void Cource::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	//m_inBox.Render(view, proj);

	m_model->Draw(m_directX11.GetContext().Get(), *m_directX11.Get().GetStates(), m_world, view, proj);
}

void Cource::CreateResource()
{
	m_model = DirectX::Model::CreateFromCMO(m_directX11.GetDevice().Get(), L"Resources\\Model\\MyGameCource_01.cmo", *m_directX11.Get().GetEffect());

}

