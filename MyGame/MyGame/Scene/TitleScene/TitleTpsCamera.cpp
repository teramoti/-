#include "TitleTpsCamera.h"

TitleTpsCamera::TitleTpsCamera(int w, int h) :
	Camera(static_cast<float>(w), static_cast<float>(h))
{
	m_targetPos = DirectX::SimpleMath::Vector3::Zero;
	m_targetRotation= DirectX::SimpleMath::Vector3::Zero;
	m_targetAngle = 0.0f;

	Object = nullptr;
}

TitleTpsCamera::~TitleTpsCamera()
{

}

void TitleTpsCamera::Update()
{
	DirectX::SimpleMath::Vector3 refpos, eyepos;
	
	SetTranslation(Object->GetTranslation());
	SetAngle(-Object->GetAngle());
	
	DirectX::SimpleMath::Matrix world;

	world = Object->GetWorld();
	m_targetPos.x = world._41;
	m_targetPos.y = world._42;
	m_targetPos.z = world._43;

	world._41 = 0;
	world._42 = 0;
	world._43 = 0;

	DirectX::SimpleMath::Quaternion rotation;
	rotation = DirectX::SimpleMath::Quaternion::CreateFromRotationMatrix(world);
	
	//TPSカメラ
	refpos = m_targetPos + DirectX::SimpleMath::Vector3(0, 1, 0);

	DirectX::SimpleMath::Vector3 cameraV(0.0f, 2.0f, 5.0f);

	DirectX::SimpleMath::Matrix rot = world;
	cameraV = DirectX::SimpleMath::Vector3::TransformNormal(cameraV, rot);

	eyepos = refpos + cameraV;
	Seteyepos(eyepos);
	Setrefpos(refpos);

	Camera::Update();
}
//----------------------------------------------------------------------
//! @brief Tpsカメラクラスの位置の設定用関数
//!
//! @param targetPos
//!
//! @return なし
//----------------------------------------------------------------------
void TitleTpsCamera::SetTranslation(DirectX::SimpleMath::Vector3 trangetpos)
{
	m_targetPos = trangetpos;
}
//----------------------------------------------------------------------
//! @brief Tpsカメラクラスの角度の設定用関数
//!
//! @param targetPos
//!
//! @return なし
//----------------------------------------------------------------------
void TitleTpsCamera::SetAngle(float rotation)
{
	m_targetAngle = rotation;
}

void TitleTpsCamera::SetObject3D(Teramoto::Object3D * object3D)
{
	Object = object3D;
}

DirectX::SimpleMath::Vector3 TitleTpsCamera::GetRotation()
{
	return m_targetRotation;
}
float TitleTpsCamera::GetAngle()
{
	return m_targetAngle;
}
