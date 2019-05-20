#include "MyCollision.h"

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();
public:
	bool CollisionBox2Box(MyCollision::Box box1, MyCollision::Box box2);


	//内側の当たり判定
	static bool HitMap(DirectX::SimpleMath::Vector3 playerPos, DirectX::SimpleMath::Vector3 mapPos, float playerRadius, DirectX::SimpleMath::Vector3 mapRadius)
	{
		float sqDist = SqDistPointBox(playerPos, mapPos, mapRadius);

		if (playerRadius * playerRadius >= sqDist)
		{
			return true;
		}

		return false;
	}

	//外側の当たり判定
	static bool HitMap2(DirectX::SimpleMath::Vector3 playerPos, DirectX::SimpleMath::Vector3 mapPos, float playerRadius, DirectX::SimpleMath::Vector3 mapRadius)
	{
		float sqDist = SqDistPointBox(playerPos, mapPos, mapRadius);

		if (playerRadius * playerRadius <= sqDist)
		{
			return true;
		}

		return false;
	}
	//点とボックスの間の最短距離の平方を計算する関数
	static float SqDistPointBox(const DirectX::SimpleMath::Vector3& p, const DirectX::SimpleMath::Vector3& b, const DirectX::SimpleMath::Vector3& c)
	{
		float point[3] = { p.x, p.y, p.z };
		float min[3] = { b.x - c.x, b.y - c.y, b.z - c.z, };
		float max[3] = { b.x + c.x, b.y + c.y, b.z + c.z, };

		float sqDist = 0.0f;
		for (int i = 0; i < 3; i++)
		{
			float v = point[i];
			if (v < min[i]) sqDist += (min[i] - v) * (min[i] - v);
			if (v > max[i]) sqDist += (v - max[i]) * (v - max[i]);
		}
		return sqDist;
	}
	static float Plane_Length(const MyCollision::Planar& plane, const DirectX::SimpleMath::Vector3& q)
	{
		float l;
		l = plane.p.x*q.x + plane.p.y*q.y + plane.p.z*q.z + plane.p.w;

		return l;
	}

	static bool HitCheckSphere(MyCollision::Sphere& sphere, const  MyCollision::Planar & plane,DirectX::SimpleMath::Vector3* p)
	{
		if (!&sphere || !& plane)return false;

		float len = Plane_Length(plane, sphere.Center);

		if (len > sphere.Radius) return false;

		if (p)
		{
			len = sphere.Radius - len;
			*p = DirectX::SimpleMath::Vector3(plane.p.x, plane.p.y, plane.p.z)*len;

		}
		return true;

	}

};