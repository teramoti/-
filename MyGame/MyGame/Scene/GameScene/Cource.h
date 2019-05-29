#pragma once
#include "../../GameSystem/Object.h"
#include "../../Collison/MyCollisionNode.h"

class Cource : public Teramoto::Object3D
{

public:
	Cource();
	~Cource();

	//初期化処理
	void Initilize();
	//更新処理
	void Update();
	//描画処理
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	void CreateResource();
private:

private:
	std::unique_ptr<DirectX::Model> m_model;

};