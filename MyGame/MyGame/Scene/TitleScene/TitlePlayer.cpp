
#include <d3d11.h>
#include <SimpleMath.h>
#include <KeyBoard.h>
#include "../../GameSystem/InputManager.h"

#include "TitlePlayer.h"
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace System;

TitlePlayer::TitlePlayer() : m_angle(0.0f), m_rotation(Quaternion::Identity), m_velocity(Vector3::Zero),
m_pos(Vector3(0.0f, 0.0f, -0.0f)), m_acceleration(0.0f),
MAX_ACCELERATION(40.0f), MIN_ACCELERATION(0.0f), m_hitFlag(false), m_hitFlag2(false),GRAVITY(9.8f) , m_engine(false)
, m_startFlag(false)
{
}

TitlePlayer::~TitlePlayer()
{
}

void TitlePlayer::Initilize()
{
	m_Translation = Vector3::Zero;

	Load(L"Resources/Model/Player.cmo");
	m_fla = false;
	m_box.Initialize();
	m_box.SetTrans(m_Translation);
	m_box.SetSize(Vector3(1, 1, 1));

	m_sphere.Initialize();
	m_sphere.Center = Vector3(m_Translation);
	m_sphere.Radius = 1.0f;
}

void TitlePlayer::Update(bool flag)
{


	m_startFlag = flag;

	MyLib::Object3D::Update();
	m_box.Update();
	m_box.SetTrans(m_Translation);

	m_sphere.SetTrans(m_Translation);
	m_sphere.Update();

	//ÉvÉåÉCÉÑÅ[ÇÃà⁄ìÆ
	PlayerMove();
}

void TitlePlayer::Render()
{
	MyLib::Object3D::Draw();

}

void TitlePlayer::Lost()
{
}

void TitlePlayer::PlayerMove()
{
	if (InputManager::GetInstance().GetKeyboardState().Space)
	{

	}
}

void TitlePlayer::HitPlayer(bool Flag)
{
	if (Flag == true)
	{
		m_hitFlag = true;
	}
}

void TitlePlayer::HitPlayer2(bool Flag)
{
	if (Flag == true)
	{
		m_hitFlag2 = true;
	}
}
