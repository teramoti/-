#include "TpsCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

TpsCamera::TpsCamera(int w, int h) :
	Camera(static_cast<float>(w), static_cast<float>(h))
{
	m_TargetPos = Vector3::Zero;
	m_TargetRot = 0.0f;
	m_TargetRotX = 0.0f;
	m_TargetRotZ = 0.0f;

	Object = nullptr;
}

TpsCamera::~TpsCamera()
{

}

void TpsCamera::Update()
{
	Vector3 refpos, eyepos;

	SetTrans(Object->GetTranslation());
	SetAngle(Object->GetAngle());

	//TPSÉJÉÅÉâ
	refpos = Vector3(m_TargetPos.x,m_TargetPos.y, m_TargetPos.z) + Vector3(0, 1, 0);

	Vector3 cameraV(0.0f, 0.0f, -3.0f);

	Matrix rot = Matrix::CreateRotationY(m_TargetRot);
	cameraV = Vector3::TransformNormal(cameraV, rot);

	eyepos = refpos + cameraV;
	Seteyepos(eyepos);
	Setrefpos(refpos);

	Camera::Update();
}

void TpsCamera::SetTrans(DirectX::SimpleMath::Vector3 trangetpos)
{
	m_TargetPos = trangetpos;
}

void TpsCamera::SetAngle(float tragetangle)
{
	m_TargetRot = tragetangle;
}

void TpsCamera::SetAngleX(float tragetangle)
{
	m_TargetRotX = tragetangle;
}

void TpsCamera::SetAngleZ(float tragetangle)
{
	m_TargetRotZ = tragetangle;
}
void TpsCamera::SetObject3D(MyLib::Object3D * object3D)
{
	Object = object3D;
}

float TpsCamera::GetAngle()
{
	return m_TargetRot;
}

float TpsCamera::GetAngleX()
{
	return m_TargetRotX;
}

float TpsCamera::GetAngleZ()
{
	return m_TargetRotZ;
}
