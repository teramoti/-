//--------------------------------------------------------------------------------------
// File: Ball.h
//
//
// Date: 2018. 7.24
// Author: Daisuke Shimizu
//--------------------------------------------------------------------------------------

// 多重インクルード
#pragma once

// インクルード
//#include "Obj3D.h"

// Ballクラス
class Ball : public Obj3D
{
public:
	enum class MOVE
	{
		STOP,
		FORWARD,
		BACK,
		TURN_LEFT,
		TURN_RIGHT,
	};

private:
	// 速度
	DirectX::SimpleMath::Vector3 m_vel;
	// 向き
	float m_direction;

	// 移動ステート
	MOVE m_move;
public:
	// コンストラクタ
	Ball();

	// 更新関数
	bool Update(float elapsedTime) override;

	// 移動関数
	void Move(MOVE move);

	// 向きを取得する関数
	float GetDirection();

	// モデルを設定する関数
	void SetModel(DirectX::Model* model);
};