/// <summary>
/// 作成日	2017/12/06
/// 作成者	寺本 啓志
/// 用　途	各あたり判定処理クラスの宣言
/// </summary>
#pragma once

/// <summary>
/// インクルード
/// </summary>
#include<d3d11.h>
#include<SimpleMath.h>

namespace MyCollision
{



	//Segmentクラス(直線)
	class Segment
	{
	public:
		DirectX::SimpleMath::Vector3 Start;
		DirectX::SimpleMath::Vector3 Vec;
	};

	//Sphereクラス(球)
	class Sphere
	{
	public:
		DirectX::SimpleMath::Vector3 Center;
		Segment segment;
		float Radius;

		Sphere()
		{
			Radius = 1.0f;
		}
	};

	//Boxクラス(箱)
	class Box {
	public:
		// 頂点座標
		// 左上前
		DirectX::SimpleMath::Vector3 Pos0;
		// 右上前
		DirectX::SimpleMath::Vector3 Pos1;
		// 左下前
		DirectX::SimpleMath::Vector3 Pos2;
		// 右下前
		DirectX::SimpleMath::Vector3 Pos3;

		// 左上後
		DirectX::SimpleMath::Vector3 Pos4;
		// 右上後
		DirectX::SimpleMath::Vector3 Pos5;
		// 左下後
		DirectX::SimpleMath::Vector3 Pos6;
		// 右下後
		DirectX::SimpleMath::Vector3 Pos7;

	};


	//Capsuleクラス(カプセル(
	class Capsule
	{
	public:
		//底辺と天井
		Segment Segment;

		//円の半径
		float Radius;

		//未設定
		Capsule()
		{
			Segment.Start = DirectX::SimpleMath::Vector3(0, 0, 0);
			Segment.Vec = DirectX::SimpleMath::Vector3(0, 1, 0);
			Radius = 1.0f;
		}
	};
	//自作の平面クラス
	class Planar
	{
	public:
		//四つの頂点
		DirectX::SimpleMath::Vector3 Vertex[4];
		DirectX::SimpleMath::Vector4 p;

		void SetPlane(DirectX::SimpleMath::Vector3 normal, DirectX::SimpleMath::Vector3 point);
		void SetPlane(DirectX::SimpleMath::Vector3 pos1, DirectX::SimpleMath::Vector3 pos2, DirectX::SimpleMath::Vector3 pos3);

	};

	//Triangleクラス(三角形)
	class Triangle {
	public:
		//	頂点座標
		DirectX::SimpleMath::Vector3 P0;
		DirectX::SimpleMath::Vector3 P1;
		DirectX::SimpleMath::Vector3 P2;
		// 法線ベクトル
		DirectX::SimpleMath::Vector3 Normal;
		Planar plane;
	};
}

//各種処理

//球と球のあたり判定
bool CheckSphere2Sphere(const MyCollision::Sphere& _sphereA, const MyCollision::Sphere& _sphereB);
//三角形を作る関数
void ComputeTriangle(const DirectX::SimpleMath::Vector3 & _p0, const DirectX::SimpleMath::Vector3 & _p1, const DirectX::SimpleMath::Vector3 & _p2, MyCollision::Triangle * _triangle);
//直線と三角形のあたり判定
bool CheckSegment2Triangle(const MyCollision::Segment & _segment, const MyCollision::Triangle & _triangle, DirectX::SimpleMath::Vector3 * _inter);
//球と三角形のあたり判定
bool CheckSphere2Triangle(const MyCollision::Sphere & _sphere, MyCollision::Triangle & _triangle, DirectX::SimpleMath::Vector3* _inter);
//球と箱のあたり判定
bool CheckSphere2Box(const MyCollision::Sphere& _sphere, const MyCollision::Box& _box, DirectX::SimpleMath::Vector3* _inter);
//箱と箱のあたり判定
bool CheckBox2BoxAABB(MyCollision::Box _box1, MyCollision::Box _box2);
//線の結果を返す
float GetSqDistanceSegment2Segment(const MyCollision::Segment& _segment0, const MyCollision::Segment& _segment1);
//球と球のあたり判定
bool CheckSphere2Triangle(const MyCollision::Sphere& sphere1, const MyCollision::Triangle& angle, DirectX::SimpleMath::Vector3 *inter);
//点と三角形のあたり判定
bool CheckPoint2Triangle(const DirectX::SimpleMath::Vector3& _point, const MyCollision::Triangle& _triangle);
//カプセルとカプセル
bool CheckCapsule2Capsule(MyCollision::Capsule _0, MyCollision::Capsule _1);
//カプセルと箱のあたり判定
bool CheckCapsuleSphere2Box(const MyCollision::Capsule& _Capsule, const MyCollision::Box& _box, DirectX::SimpleMath::Vector3* _inter);
//カプセルと球のあたり判定
bool CheckCapsule2Sphere(const MyCollision::Capsule& _Capsule, const MyCollision::Sphere& _sphere, DirectX::SimpleMath::Vector3* _inter);

//箱と平面のあたり判定(基本地面との判定
bool CheckPlane2box(const MyCollision::Planar& _planer,const MyCollision::Box& _box,DirectX::SimpleMath::Vector3* _inter);
inline float Clamp(float _x, float _min, float _max);