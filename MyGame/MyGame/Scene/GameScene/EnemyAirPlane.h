#ifndef ENEMY_AIR_PLANE
#define ENEMYA_IR_PLANE
#include ".././../GameSystem/Object.h"
#include <Model.h>
class EnemyAirPlane : Teramoto::Object3D
{
public:
	//コンストラクタ
	EnemyAirPlane();
	//デストラクタ
	~EnemyAirPlane();

	//初期化処理
	void Initilize();

	//更新処理
	void Update();

	//描画処理
	void Render();

	//リソースの生成
	void CreateResources();

private:

	//モデルの定義
	std::unique_ptr<DirectX::Model> m_model;
};

#endif // !ENEMY_AIR_PLANE
