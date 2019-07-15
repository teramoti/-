#pragma once
#include "../../GameSystem/Object.h"
#include "../../Collison/MyCollisionNode.h"


class Cource : public Teramoto::Object3D
{

public:
	Cource();
	~Cource();

	//‰Šú‰»ˆ—
	void Initilize();
	//XVˆ—
	void Update();
	//•`‰æˆ—
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	void CreateResource();

	BoxNode& GetBox()
	{
		return m_inBox;
	}
private:

	//“à‘¤‚Ì‚ ‚½‚è”»’è

	BoxNode m_inBox;
private:
	std::unique_ptr<DirectX::Model> m_model;

};