#pragma once
#include "../../GameSystem/Object.h"
#include "../../Collison/MyCollisionNode.h"

class Cource : public MyLib::Object3D
{

public:
	Cource();
	~Cource();

	void Initilize();//‰Šú‰»ˆ—
	void Update();//XVˆ—
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);//•`‰æˆ—()
	void CreateResource();
private:

private:
	std::unique_ptr<DirectX::Model> m_model;

};