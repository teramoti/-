#pragma once
#ifndef SUBJECT_DEFINED
#define SUBJECT_DEFINED

#include <vector>
#include <algorithm>

#include <d3d11.h>
#include <SimpleMath.h>

#include "Observer.h"

class Observer;

class Subject
{
public:
	virtual void Attach(Observer* observer);
	virtual void Detach(Observer* observer);
	virtual void Notify(DirectX::SimpleMath::Vector3& pos);

private:
	std::vector<Observer*> m_observerVector;
};

#endif	// SUBJECT_DEFINED
