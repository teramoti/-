//Ž›–{Œ[Žu
//Observer
#pragma once
#ifndef OBSERVER_DEFINED
#define OBSERVER_DEFINED

#include <d3d11.h>

#include <iostream>
#include <string>
#include <SimpleMath.h>
#include "../Scene/GameScene/MyAirPlane.h"
#include "IOberver.h"
//#include "Position.h"

class Observer : public IObserver
{
public:
	Observer(const std::string& name,MyAirPlane* player);

	void Update(DirectX::SimpleMath::Vector3& pos);

private:
	std::string m_name;
	DirectX::SimpleMath::Vector3 m_pos;

	MyAirPlane* m_player;

};

#endif	// OBSERVER_DEFINED
