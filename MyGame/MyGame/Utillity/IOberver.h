//Ž›–{Œ[Žu
//IObserver

#pragma once
#ifndef IOBSERVER_DEFINED
#define IOBSERVER_DEFINED

#include <d3d11.h>
#include <SimpleMath.h>

class IObserver
{
public:
	
	virtual void Update(DirectX::SimpleMath::Vector3& pos) = 0;

};

#endif	// IOBSERVER_DEFINED
