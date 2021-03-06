#pragma once
#include "../../GameSystem/Object.h"
#include "../../Collison/Collision.h"
#include "../../Utillity/DirectX11.h"
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

	Collision::Box& GetBox()
	{
		return m_inBox;
	}
private:

	//内側のあたり判定
	Collision::Box m_inBox;
	DirectX11& m_directX = DirectX11::Get();
private:
	std::unique_ptr<DirectX::Model> m_model;

};