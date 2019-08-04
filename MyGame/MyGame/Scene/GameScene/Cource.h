#pragma once
#include "../../GameSystem/Object.h"
#include "../../Collison/Collision.h"
#include "../../Utillity/DirectX11.h"
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

	Collision::Box& GetBox()
	{
		return m_inBox;
	}
private:

	//“à‘¤‚Ì‚ ‚½‚è”»’è
	Collision::Box m_inBox;
	DirectX11& m_directX = DirectX11::Get();
private:
	std::unique_ptr<DirectX::Model> m_model;

};