//--------------------------------------------------------------------------------------
// File: Ball.h
//
//
// Date: 2018. 7.24
// Author: Daisuke Shimizu
//--------------------------------------------------------------------------------------

// インクルード
#include "pch.h"
#include "Ball.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
/// <summary>
/// コンストラクタ
/// </summary>
Ball::Ball()
	:Obj3D(), m_direction(0.0f),m_move(MOVE::STOP)
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime"></param>
/// <returns></returns>
bool Ball::Update(float elapsedTime)
{
	// 加速度
	Vector3 a;

	switch (m_move)
	{
	case MOVE::FORWARD:
		a.z = -0.01f;
		break;
	case MOVE::BACK:
		a.z = 0.01f;
		break;
	case MOVE::TURN_LEFT:
		m_direction += XMConvertToRadians(1);
		break;
	case MOVE::TURN_RIGHT:
		m_direction -= XMConvertToRadians(1);
		break;
	}

	// 止める
	m_move = MOVE::STOP;

	// 加速度をBallの向きに回転させる
	Matrix rotY = Matrix::CreateRotationY(m_direction);
	a = Vector3::Transform(a, rotY);
	// 速度に加速度を足す
	m_vel += a;
	// 位置に速度を足す
	m_position += m_vel;

	// 移動方向にボールを回転させる
	Vector3 axis(1, 0, 0);
	rotY = Matrix::CreateRotationY(atan2f(m_vel.x, m_vel.z));
	axis = Vector3::Transform(axis, rotY);

	// Ballの半径が1なので移動量が回転量になる
	m_rotation *= Quaternion::CreateFromAxisAngle(axis, m_vel.Length());
	// 摩擦により減速させる(適当)
	m_vel *= 0.99f;

	// ワールド行列を作成
	m_world = Matrix::CreateFromQuaternion(m_rotation)
		* Matrix::CreateTranslation(m_position);

	return true;
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="move"></param>
void Ball::Move(MOVE move)
{
	m_move = move;
}

/// <summary>
/// 向きを取得する関数
/// </summary>
/// <returns></returns>
float Ball::GetDirection()
{
	return m_direction;
}

/// <summary>
/// モデルを設定する関数
/// </summary>
/// <param name="model"></param>
void Ball::SetModel(DirectX::Model * model)
{
	m_model = model;
	// Effectを更新する
	m_model->UpdateEffects([&](IEffect* effect)
	{
		auto lights = dynamic_cast<IEffectLights*>(effect);
		if (lights)
		{
			// ピクセル単位でライトの計算をする
			lights->SetPerPixelLighting(true);
		}
	});
}
