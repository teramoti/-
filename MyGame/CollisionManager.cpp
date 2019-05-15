#include "../../pch.h"
#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

bool CollisionManager::CollisionBox2Box(Box box1, Box box2)
{
	if (CheckBox2BoxAABB(box1, box2)==true)
	{
		return true;
	}
	return false;
}
