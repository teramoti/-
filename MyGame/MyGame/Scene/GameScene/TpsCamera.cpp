#include "TpsCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

TpsCamera::TpsCamera(int w, int h) :
	Camera(static_cast<float>(w), static_cast<float>(h))
{
	m_targetPos = Vector3::Zero;
	m_targetRotation= Vector3::Zero;
	m_targetAngle = 0.0f;

	Object = nullptr;
}

TpsCamera::~TpsCamera()
{

}

void TpsCamera::Update()
{
	Vector3 refpos, eyepos;

	SetTranslation(Object->GetTranslation());
	SetAngle(Object->GetAngle());

	//TPSカメラ
	refpos = Vector3(m_targetPos) + Vector3(0, 1, 0);

	Vector3 cameraV(0.0f, 0.0f, -4.0f);

	Matrix rot = Matrix::CreateRotationY(m_targetAngle);
	cameraV = Vector3::TransformNormal(cameraV, rot);

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
void TpsCamera::SetTranslation(DirectX::SimpleMath::Vector3 trangetpos)
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
void TpsCamera::SetAngle(float rotation)
{
	m_targetAngle = rotation;
}

void TpsCamera::SetObject3D(Teramoto::Object3D * object3D)
{
	Object = object3D;
}

DirectX::SimpleMath::Vector3 TpsCamera::GetRotation()
{
	return m_targetRotation;
}
float TpsCamera::GetAngle()
{
	return m_targetAngle;
}
