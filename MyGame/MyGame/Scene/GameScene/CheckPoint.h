#pragma once
#include "../../GameSystem/Object.h"

class CheckPoint : public Teramoto::Object3D
{
public:
	CheckPoint();
	~CheckPoint();

	void Initilize();
	void Update();
	void Render(DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj);
	//チェックポイントの変数
	bool CheckBlock[3];
	//最後のゴールフラグ
	bool m_FinalFlag;


	bool Checkhit1(bool flag);
	bool Checkhit2(bool flag);
	bool Checkhit3(bool flag);
	bool GetFlag();
	//ゴールのフラグ
	bool m_Flag;


private:

	//当たり判定の設定
	// m_box[3];
	std::unique_ptr<DirectX::Model> m_model;

};