#pragma once


#include <Model.h>
#include <CommonStates.h>

#include <Effects.h>
#include "../../Scene/GameScene/TpsCamera.h"
#include "../../Collison/Collision.h"
#include "../../GameSystem/Object.h"
#include "../../Utillity/DirectX11.h"
#include "../GameScene/Shadow.h"

class TitleAirPlane : public Teramoto::Object3D
{

public:
	//コンストラクタ
	TitleAirPlane();
	//デストラクタ
	~TitleAirPlane();
public:

	//初期化処理
	void Initilize();
	void CreateResource();
	//更新処理
	void Update();
	//描画処理()
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	//削除する処理
	void Lost();
	//プレイヤーを移動せる関数
	void MyAirPlaneMove();

	//velcityのGet関数
	DirectX::SimpleMath::Vector3 GetVelotity()
	{
		return m_velocity;
	}
	//velcityのセット用関数
	void SetVel(DirectX::SimpleMath::Vector3 vel)
	{
		m_velocity = vel;
	}



private:

	//影の描画
	Shadow* m_shadow;

	//ポジション
	DirectX::SimpleMath::Vector3 m_pos;

	//回転
	DirectX::SimpleMath::Quaternion m_rotation;

	//速度
	DirectX::SimpleMath::Vector3 m_velocity;

	//加速度
	float m_acceleration;

	//重力
	const float GRAVITY = 0.98f;
	//最高速度
	const float MAX_ACCELERATION = 80.0f;
	//最低速度
	const float MIN_ACCELERATION = 0.0f;

public:
	//角度
	float m_angle;

	//モデルの定義
	std::unique_ptr<DirectX::Model> m_model;
	//速度用変数
	DirectX::SimpleMath::Vector3 vec;

	DirectX11& m_directX = DirectX11::Get();
};

