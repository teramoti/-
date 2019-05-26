//----------------------------------------
/// <summary>
///	コースのクラス
/// GS2 寺本 啓志
/// </summary>
//----------------------------------------
#include "SkyDome.h"



SkyDome::SkyDome()
{
	
	
}
SkyDome::~SkyDome()
{

}


void SkyDome::Initilize()
{
	//Load(L"Resources/Model/SkyDome.cmo");

	 m_scale *= 12.0f;
	m_world = DirectX::SimpleMath::Matrix::Identity;
	m_translation = DirectX::SimpleMath::Vector3(0, -300.0f, 0);
	m_rotation = DirectX::SimpleMath::Quaternion(0, 0, 0,0);

	m_world = DirectX::SimpleMath::Matrix::CreateScale( m_scale)*DirectX::SimpleMath::Matrix::CreateTranslation(m_translation)*
		DirectX::SimpleMath::Matrix::CreateRotationX(m_rotation.x)
		*DirectX::SimpleMath::Matrix::CreateRotationY(m_rotation.y)*DirectX::SimpleMath::Matrix::CreateRotationZ(m_rotation.z);
}

void SkyDome::Update()
{
	m_rotation.y += SKYDOME_ROTATION_Y;
	MyLib::Object3D::Update();

}

void SkyDome::ReUpdate()
{
}

void SkyDome::Render()
{
	//SetLight();
	//Draw();
}
