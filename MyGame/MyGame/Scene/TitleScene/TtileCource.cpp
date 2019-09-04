#include <d3d11.h>
#include <SimpleMath.h>
#include <KeyBoard.h>

#include "../../GameSystem/InputManager.h"

#include "TtileCource.h"


TitleCourceObject::TitleCourceObject() 
{

}

TitleCourceObject::~TitleCourceObject()
{
}

void TitleCourceObject::Initilize()
{
	m_translation = DirectX::SimpleMath::Vector3(0, 0, 0);
	CreateResource();
}

void TitleCourceObject::CreateResource()
{
	m_model = DirectX::Model::CreateFromCMO(m_directX11.GetDevice().Get(), L"Resources\\Model\\TitleCource.cmo", *m_directX11.Get().GetEffect());

}

void TitleCourceObject::Update()
{
	Teramoto::Object3D::Update();


}

void TitleCourceObject::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	m_model->Draw(m_directX11.GetContext().Get(), *m_directX11.Get().GetStates(), m_world, view, proj);
}

void TitleCourceObject::Lost()
{
}
