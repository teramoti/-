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
	void Render();//描画処理()

private:
		//コースあたり判定
	BoxNode m_box[5];
};