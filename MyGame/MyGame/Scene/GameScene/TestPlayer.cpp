
#include <d3d11.h>
#include <SimpleMath.h>
#include <KeyBoard.h>
#include "../../GameSystem/InputManager.h"

#include "TestPlayer.h"

//using namespace DirectX;
//using namespace DirectX::SimpleMath;
using namespace System;

TestPlayer::TestPlayer() : m_angle(0.0f), m_rotation(DirectX::SimpleMath::Quaternion::Identity), m_velocity(DirectX::SimpleMath::Vector3::Zero),
m_pos(DirectX::SimpleMath::Vector3(0.0f, 0.0f, -0.0f)), m_acceleration(0.0f),
MAX_ACCELERATION(40.0f), MIN_ACCELERATION(0.0f),GRAVITY(9.8f)
, m_startFlag(false)
{
}

TestPlayer::~TestPlayer()
{
}

void TestPlayer::Initilize()
{
	m_Translation = DirectX::SimpleMath::Vector3(0,4,0);

	Load(L"Resources/Model/Player.cmo");
	m_box.Initialize();
	m_box.SetTrans(m_Translation);
	m_box.SetSize(DirectX::SimpleMath::Vector3(1, 1, 1));

	m_sphere.Initialize();
	m_sphere.Center = DirectX::SimpleMath::Vector3(m_Translation);
	m_sphere.Radius = 1.0f;
}

void TestPlayer::Update(bool flag)
{


	m_startFlag = flag;

	MyLib::Object3D::Update();
	m_box.Update();
	m_box.SetTrans(m_Translation);

	m_sphere.SetTrans(m_Translation);
	m_sphere.Update();

	//プレイヤーの移動
	PlayerMove();

}

void TestPlayer::Render()
{
	MyLib::Object3D::Draw();
	//mbox.Render();
	//m_sphere.Render();
}

void TestPlayer::Lost()
{
}

void TestPlayer::PlayerMove()
{
	bool keyFlag = false;

	vec = DirectX::SimpleMath::Vector3::Zero;

	//プレイヤーの移動
	//上移動
	if (m_startFlag == true)
	{
		if (System::InputManager::GetInstance().GetKeyboardState().Up)
		{
			vec.z = 0.1f/* * m_boost*/;

			m_acceleration += 0.2f;
		}
		else
		{
			vec.z = 0.1f/* * m_boost*/;

			m_acceleration *= 0.98f;
		}

		//下移動
		if (System::InputManager::GetInstance().GetKeyboardState().Down)
		{
			m_acceleration *= 0.98f;

			keyFlag = true;
		}


		//右移動
		if (System::InputManager::GetInstance().GetKeyboardState().Left)
		{
			m_angle += DirectX::XMConvertToRadians(2.0f);

			m_rotation = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f), DirectX::XMConvertToRadians(1.5f));
			m_velocity = DirectX::SimpleMath::Vector3::Transform(m_velocity, m_rotation);
			SetRot(m_rotation);

		}

		//左移動
		if (System::InputManager::GetInstance().GetKeyboardState().Right)
		{
			m_angle -= DirectX::XMConvertToRadians(2.0f);

			m_rotation = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f), DirectX::XMConvertToRadians(-1.5f));
			m_velocity = DirectX::SimpleMath::Vector3::Transform(m_velocity, m_rotation);

			SetRot(DirectX::SimpleMath::Quaternion(m_rotation.w, m_rotation.x, m_rotation.y - 0.3f, m_rotation.z));
		}
	}

	//加速度MAX
	if (m_acceleration > MAX_ACCELERATION)
	{
		m_acceleration = MAX_ACCELERATION;
	}

	//加速度MIN
	if (m_acceleration < MIN_ACCELERATION)
	{
		m_acceleration = MIN_ACCELERATION;
	}


	//角度の設定

	m_rotation = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3(0.0f, 1.0f, 0.0f), m_angle);
	vec = DirectX::SimpleMath::Vector3::Transform(vec, m_rotation);
	m_velocity = vec * (m_acceleration);


	// 速度に重力加速度を足す
	m_velocity.y -= GRAVITY * (1.0f / 60.0f);

	// 位置に速度を足す
	m_pos += m_velocity;

	// 地面にめり込まないための処理を書く
	if (m_pos.y < 0.0f)
	{
		m_pos.y = 0.0f;
	}
	m_Translation = m_pos;

	SetTranslation(m_Translation);//位置の設定
	SetAngle(m_angle);//角度の設定
	SetRot(m_rotation);//回転の設定

}
