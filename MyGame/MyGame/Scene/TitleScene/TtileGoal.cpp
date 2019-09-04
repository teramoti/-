#include <d3d11.h>
#include <SimpleMath.h>
#include <KeyBoard.h>

#include "../../GameSystem/InputManager.h"

#include "TtileGoal.h"


TitleGoalObject::TitleGoalObject() 
{

}

TitleGoalObject::~TitleGoalObject()
{
}

void TitleGoalObject::Initilize()
{
	//�ʒu�ݒ�
	m_translation = DirectX::SimpleMath::Vector3(0, 0, 600);
	//�N���G�C�g���\�[�X�֐����Ă�
	CreateResource();
}

void TitleGoalObject::CreateResource()
{
	//���f���̐ݒ�
	m_model = DirectX::Model::CreateFromCMO(m_directX11.GetDevice().Get(), L"Resources\\Model\\Goal.cmo", *m_directX11.Get().GetEffect());

}

void TitleGoalObject::Update()
{
	//�X�V
	Teramoto::Object3D::Update();


}

void TitleGoalObject::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	//���f���̕`��
	m_model->Draw(m_directX11.GetContext().Get(), *m_directX11.Get().GetStates(), m_world, view, proj);
}

void TitleGoalObject::Lost()
{
}
