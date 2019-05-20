#pragma once
#include "../../GameSystem/TpsCamera.h"
#include "../../GameSystem/Object.h"
#include "../../Collison/MyCollisionNode.h"

class TestPlayer : public MyLib::Object3D
{

public:
	TestPlayer();//コンストラクタ
	~TestPlayer();//デストラクタ
public:

	void Initilize();//初期化処理
	void Update(bool flag);//更新処理
	void Render();//描画処理()
	void Lost();//削除する処理
	void PlayerMove();	//プレイヤーを移動せる関数

	//velcityのGet関数
	DirectX::SimpleMath::Vector3 GetVel()
	{
		return m_velocity;
	}
	//velcityのセット用関数
	void SetVel(DirectX::SimpleMath::Vector3 vel)
	{
		m_velocity = vel;
	}


	BoxNode& GetBox()
	{
		return m_box;
	}

private:

	//Playerの情報
	DirectX::SimpleMath::Vector3 m_pos;//ポジション

	DirectX::SimpleMath::Quaternion m_rotation;//回転

	DirectX::SimpleMath::Vector3 m_velocity;//速度
											
	//加速度
	float m_acceleration;

	const float GRAVITY=0.98f;//重力
	const float MAX_ACCELERATION=45.0f;//最高速度
	const float MIN_ACCELERATION= 0.0f; //最低速度

	float m_angle = 0.0f;	//角度



	bool m_startFlag;//始まったかのフラグ管理
	DirectX::SimpleMath::Vector3 vec;//速度用変数

	BoxNode m_box;//ボックスのNode

	SphereNode m_sphere;//SphereのNode

};

