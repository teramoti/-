#pragma once
#include "../../GameSystem/TpsCamera.h"
#include "../../GameSystem/Object.h"
#include "../../Collison/MyCollisionNode.h"

class TitlePlayer : public MyLib::Object3D
{

public:
	TitlePlayer();//コンストラクタ
	~TitlePlayer();//デストラクタ
public:

	void Initilize();//初期化処理
	void Update(bool flag);//更新処理
	void Render();//描画処理()
	void Lost();//削除する処理
	//プレイヤーを移動せる関数
	void PlayerMove();

	DirectX::SimpleMath::Vector3 GetVel()
	{
		return m_velocity;
	}

	void HitPlayer(bool Flag);

	void HitPlayer2(bool Flag);

	void SetVel(DirectX::SimpleMath::Vector3 vel)
	{
		m_velocity = vel;
	}

	bool GetEngine()
	{
		return m_engine;
	}
	const float GRAVITY;

	BoxNode& GetBox()
	{
		return m_box;
	}
private:


	//モンスター01の情報
	DirectX::SimpleMath::Vector3 m_pos;
	DirectX::SimpleMath::Quaternion m_rotation;
	DirectX::SimpleMath::Vector3 m_velocity;
	//速さ
	const float m_speed = 3.0f;
	//加速度
	float m_acceleration;

	const float MAX_ACCELERATION;
	const float MIN_ACCELERATION;

	//角度
	float m_angle = 0.0f;
	//進化後のスピード
	float evoSpeed = 1.0f;
	//ゴールした回数
	int m_goalCount = 0;
	//ポイントの数
	int m_maxGoalFlag;
	//ポイントの回数
	int m_goalFlag = 0;
	//現在のポイント
	int m_point = 0;

	bool m_startFlag;
	DirectX::SimpleMath::Vector3 v3;

	//大きさ
	DirectX::SimpleMath::Vector3 m_size = { 2.0f,2.0f,2.0f };

	//角度
	DirectX::SimpleMath::Vector3 m_ang01 = { 0.0f,1.0f,0.0f };

	DirectX::SimpleMath::Quaternion m_rot01;

	bool m_hitFlag;
	bool m_hitFlag2;
	bool m_fla;
	BoxNode m_box;

	SphereNode m_sphere;
	bool m_engine;
};

