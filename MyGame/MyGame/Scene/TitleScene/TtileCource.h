#pragma once


#include <Model.h>
#include <CommonStates.h>

#include <Effects.h>
#include "../../Scene/GameScene/TpsCamera.h"
#include "../../Collison/Collision.h"
#include "../../GameSystem/Object.h"
#include "../../Utillity/DirectX11.h"
#include "../GameScene/Shadow.h"

class TitleCourceObject : public Teramoto::Object3D
{

public:
	//コンストラクタ
	TitleCourceObject();
	//デストラクタ
	~TitleCourceObject();
public:

	//初期化処理
	void Initilize();
	void CreateResource();
	//更新処理
	void Update();
	//描画処理()
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	//削除する処理
	void Lost();

private:
	std::unique_ptr<DirectX::Model> m_model;
	
	DirectX11& m_directX = DirectX11::Get();
};

