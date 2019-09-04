#include <d3d11.h>
#include <SimpleMath.h>
#include <KeyBoard.h>

#include "../../GameSystem/InputManager.h"

#include "Goal.h"


GoalObject::GoalObject() 
{

}

GoalObject::~GoalObject()
{
}

void GoalObject::Initilize()
{
	m_translation = DirectX::SimpleMath::Vector3(0, -50, 0);
	CreateResource();
}

void GoalObject::CreateResource()
{
	m_model = DirectX::Model::CreateFromCMO(m_directX11.GetDevice().Get(), L"Resources\\Model\\Goal.cmo", *m_directX11.Get().GetEffect());

}

void GoalObject::Update()
{
	Teramoto::Object3D::Update();


}

void GoalObject::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	m_model->Draw(m_directX11.GetContext().Get(), *m_directX11.Get().GetStates(), m_world, view, proj);
}

void GoalObject::Lost()
{
}
