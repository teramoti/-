//#include "../../../pch.h"
#include "Cource.h"
#include "../../Collison/DebugBox.h"


Cource::Cource()
{
}

Cource::~Cource()
{
	m_model.reset();
}

void Cource::Initilize()
{
	m_directX11.Get().GetEffect()->SetDirectory(L"Resources\\Model");

	CreateResource();
	
	m_inBox.c=(DirectX::SimpleMath::Vector3(1000/2,0,0));
	m_inBox.r=(DirectX::SimpleMath::Vector3(360 ,50,360));


	m_translation = DirectX::SimpleMath::Vector3(0, -1, 0);
}

void Cource::Update()
{
	Object3D::Update();
}

void Cource::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{

	DirectX::SimpleMath::Matrix world;
	world = DirectX::SimpleMath::Matrix::CreateScale(m_inBox.r)*DirectX::SimpleMath::Matrix::CreateTranslation(m_inBox.c);
	m_model->Draw(m_directX11.GetContext().Get(), *m_directX11.Get().GetStates(), m_world, view,proj);

	DebugBox* playerdebugbox = new DebugBox(m_directX.GetDevice().Get(), m_inBox.c, m_inBox.r);

	playerdebugbox->Draw(m_directX.GetContext().Get(), *m_directX.Get().GetStates(), world, view, proj);


}

void Cource::CreateResource()
{
	m_model = DirectX::Model::CreateFromCMO(m_directX11.GetDevice().Get(), L"Resources\\Model\\MyGameCource_01.cmo", *m_directX11.Get().GetEffect());

}

