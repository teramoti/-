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
	//位置設定
	m_translation = DirectX::SimpleMath::Vector3(0, 0, 600);
	//クリエイトリソース関数を呼ぶ
	CreateResource();
}

void TitleGoalObject::CreateResource()
{
	//モデルの設定
	m_model = DirectX::Model::CreateFromCMO(m_directX11.GetDevice().Get(), L"Resources\\Model\\Goal.cmo", *m_directX11.Get().GetEffect());

}

void TitleGoalObject::Update()
{
	//更新
	Teramoto::Object3D::Update();


}

void TitleGoalObject::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	//モデルの描画
	m_model->Draw(m_directX11.GetContext().Get(), *m_directX11.Get().GetStates(), m_world, view, proj);
}

void TitleGoalObject::Lost()
{
}
