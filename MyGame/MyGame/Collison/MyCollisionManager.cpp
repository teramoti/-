#include "MyCollisionManager.h"

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

bool CollisionManager::CollisionBox2Box(MyCollision::Box box1, MyCollision::Box box2)
{
	if (CheckBox2BoxAABB(box1, box2)==true)
	{
		return true;
	}
	return false;
}
