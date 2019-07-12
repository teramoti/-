#pragma once
#ifndef ENEMY_AIR_PLANE
#define ENEMY_AIR_PLANE
#include "MyNeuralNetwork.h"
#include "../../../StepTimer.h"
#include <Model.h>
#include <CommonStates.h>

#include <Effects.h>
#include "TpsCamera.h"

#include "../../GameSystem/Object.h"
#include "../../Collison/MyCollisionNode.h"

class EnemyAirPlane : Teramoto::Object3D
{
public:

	EnemyAirPlane();
	~EnemyAirPlane();

public:
	//初期化処理
	void Initilize();


	//更新処理
	void Update(DX::StepTimer& timer);
	//描画処理()
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	//削除する処理
	void Lost();

	//リソースの生成
	void CreateResources();

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

	// Create neural network object
	NeuralNetwork	m_theAngleBrain;

	// Create neural network object
	NeuralNetwork	m_theSpeedBrain;


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
	const float MAX_ACCELERATION = 45.0f;
	//最低速度
	const float MIN_ACCELERATION = 0.0f;

public:
	//角度
	float m_angle;
	//始まったかのフラグ管理
	bool m_startFlag;

	//モデルの定義
	std::unique_ptr<DirectX::Model> m_model;
	//速度用変数
	DirectX::SimpleMath::Vector3 vec;


	//ボックスのNode
	BoxNode m_box;
};

#endif // !ENEMY_AIR_PLANE
