//Ž›–{Œ[Žu
//Observer
#pragma once
#ifndef OBSERVER_DEFINED
#define OBSERVER_DEFINED

#include <d3d11.h>

#include <iostream>
#include <string>
#include <SimpleMath.h>

#include "Subject.h"

#include "../Scene/GameScene/MyAirPlane.h"
#include "IOberver.h"

//#include "Position.h"

class Subject;

class Observer : public IObserver
{
public:
	Observer(MyAirPlane* player);

	void Update(Subject* subject);

private:
	std::string m_name;
	DirectX::SimpleMath::Vector3 m_pos;

	MyAirPlane* m_player;
	Subject* m_subject;
};

#endif	// OBSERVER_DEFINED
