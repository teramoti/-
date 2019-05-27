#pragma once
#include "../../GameSystem/Object.h"
#include "../../Collison/MyCollisionNode.h"

class Cource : public MyLib::Object3D
{

public:
	Cource();
	~Cource();

	void Initilize();//初期化処理
	void Update();//更新処理
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);//描画処理()
	void CreateResource();
private:

private:
	std::unique_ptr<DirectX::Model> m_model;

};