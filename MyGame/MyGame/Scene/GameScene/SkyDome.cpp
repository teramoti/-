//----------------------------------------
/// <summary>
///	コースのクラス
/// GS2 寺本 啓志
/// </summary>
//----------------------------------------
#include "SkyDome.h"
using Microsoft::WRL::ComPtr;
using namespace DirectX;
using namespace DirectX::SimpleMath;
SkyDome::SkyDome()
{
	
	
}
SkyDome::~SkyDome()
{

}


void SkyDome::Initilize()
{
	Load(L"Resources/Model/SkyDome.cmo");

	m_Scale *= 12.0f;
	m_World = Matrix::Identity;
	m_Translation = Vector3(0, -300.0f, 0);
	m_Rotation = Vector3(0, 0, 0);

	m_World = Matrix::CreateScale(m_Scale)*Matrix::CreateTranslation(m_Translation)*Matrix::CreateRotationX(m_Rotation.x)
		*Matrix::CreateRotationY(m_Rotation.y)*Matrix::CreateRotationZ(m_Rotation.z);
}

void SkyDome::Update()
{
	m_Rotation.y += SKYDOME_ROTATION_Y;
	MyLib::Object3D::Update();

}

void SkyDome::ReUpdate()
{
}

void SkyDome::Render()
{
	SetLight();
	Draw();
}
