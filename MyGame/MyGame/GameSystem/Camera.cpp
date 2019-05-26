//#include "../../pch.h"
#include "Camera.h"



using namespace MyLib;
Camera::Camera(float w, float h)
	: m_Eyepos(0, 0, 3.0f)
	, m_Refpos(0, 0, 0)
	, m_Upvec(0, 1.0f, 0)
{
	m_FovY = DirectX::XMConvertToRadians(60.0f);
	m_Aspect = (float)w / h;
	m_NearClip = 0.1f;
	m_FarClip = 1800.0f;
}

Camera::~Camera()
{

}

void Camera::Update()
{
	m_View = DirectX::SimpleMath::Matrix::CreateLookAt(m_Eyepos, m_Refpos, m_Upvec);

	m_Proj = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(m_FovY, m_Aspect, m_NearClip, m_FarClip);
}

const DirectX::SimpleMath::Matrix & Camera::GetView()
{
	// TODO: return ステートメントをここに挿入します
	return m_View;
}

const DirectX::SimpleMath::Matrix & Camera::GetProj()
{
	// TODO: return ステートメントをここに挿入します
	return m_Proj;
}

void Camera::Seteyepos(const DirectX::SimpleMath::Vector3 & eyepos)
{
	m_Eyepos = eyepos;
}

void Camera::Setrefpos(const DirectX::SimpleMath::Vector3 & refpos)
{
	m_Refpos = refpos;
}

void Camera::Setupvec(const DirectX::SimpleMath::Vector3 & upvec)
{
	m_Upvec = upvec;
}

void Camera::SetfovY(float fovY)
{
	m_FovY = fovY;
}

void Camera::Settaspect(float aspect)
{
	m_Aspect = aspect;
}

void Camera::SetanerClip(float nearclip)
{
	m_NearClip = nearclip;
}

void Camera::SetfarClip(float farclip)
{
	m_FarClip = farclip;
}

void Camera::SetTargetPos(DirectX::SimpleMath::Vector3 target)
{
	this->m_target = target;
}
