//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//
// 当たり判定ノード
//
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once

#include "../GameSystem/Object.h"
#include "MyCollision.h"
#include "../Utillity/DirectX11.h"
#include<Model.h>
// 当たり判定ノード 
class CollisionNode
{
protected:
	// デバッグ表示ON
	static bool m_DebugVisible;

public:
	CollisionNode();
	~CollisionNode();
	// setter
	static void SetDebugVisible(bool Visible) { m_DebugVisible = Visible; }

	// getter
	static bool GetDebugVisible() { return m_DebugVisible; }
	

	// モデルハンドル
	std::unique_ptr<DirectX::Model> m_model;
protected:
// メンバ変数
	//デバッグ表示用オブジェクト
	Teramoto::Object3D m_obj;

	DirectX::SimpleMath::Vector3 m_translation;

	DirectX11& m_directX11 = DirectX11::Get();
public:
// メンバ関数
	// 初期化処理
	virtual void Initialize() = 0;
	// 更新処理
	virtual void Update() = 0;
	// 描画処理
	virtual void Render(DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj) = 0;

	virtual void CreateResource()=0;
	void SetParent(Teramoto::Object3D* parent);

	void SetTrans(DirectX::SimpleMath::Vector3& trans);

};

// 球の当たり判定ノード //
class SphereNode : public CollisionNode , public MyCollision::Sphere
{
protected:
// メンバ変数
	float m_localRadius;

public:
// メンバ関数
	// コンストラクタ
	SphereNode();
	// 初期化処理
	void Initialize();
	// 更新処理
	void Update();
	// 描画処理
	void Render(DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj);

	void CreateResource();

	void SetLocalRadius(float radius) { m_localRadius = radius;}

	// 中心座標を取得する
	DirectX::SimpleMath::Vector3 GetTrans() { return m_translation; }
};

class BoxNode :public CollisionNode, public MyCollision::Box
{
protected:
// メンバ変数

	// 各辺の大きさ（x:横,y:縦,z:奥）
	DirectX::SimpleMath::Vector3 m_size;

public:
	// コンストラクタ
	BoxNode();
	// 初期化処理
	void Initialize();
	// 更新処理
	void Update();
	// 描画処理
	void Render(DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj);

	void CreateResource();

	// 各辺の大きさを設定する
	void SetSize(DirectX::SimpleMath::Vector3 size) { m_size = size;DirectX::SimpleMath::Vector3 Lsize = size /2; m_obj.SetScale(Lsize); 
	SetPointPos();
	}

	// 各辺の大きさで頂点を設定する
	void SetPointPos();

	// 中心座標を取得する
	DirectX::SimpleMath::Vector3 GetTrans() { return m_translation; }

	// 箱の大きさを取得する
	DirectX::SimpleMath::Vector3 GetSize() { return m_size; }

};

class CapsuleNode :public CollisionNode, public MyCollision::Capsule
{
private:

	float m_height;

public:
	CapsuleNode();
	// 初期化処理
	void Initialize();
	// 更新処理
	void Update();
	// 描画処理
	void Render(DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj);

	void CreateResource();
	//大きさのセット
	void SetSize(DirectX::SimpleMath::Vector3 size);
	//半径と高さのセット
	void SetHiehtRadius(float height, float radius);

	void SetPos();

	//SgmentのEndの座標を受け取る？
	DirectX::SimpleMath::Vector3 GetTrans() { return m_translation; }
};

//自作
class PlanarNode :public CollisionNode, public MyCollision::Planar
{
public:
	PlanarNode();

	void Initialize();

	void Update();

	void Render(DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix& proj);

	void CreateResource();

	//大きさを設定する(長方形、正方形を想定
	void SetVertex4(DirectX::SimpleMath::Vector3 Ver0, DirectX::SimpleMath::Vector3 Ver1, DirectX::SimpleMath::Vector3 Ver2, DirectX::SimpleMath::Vector3 Ver3);
};