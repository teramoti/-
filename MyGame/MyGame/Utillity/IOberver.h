//Ž›–{Œ[Žu
//IObserver

#pragma once
#ifndef IOBSERVER_DEFINED
#define IOBSERVER_DEFINED

#include <d3d11.h>
#include <SimpleMath.h>
#include "Subject.h"

class Subject;

class IObserver
{
public:
	
	virtual void Update(Subject* subject) = 0;

};

#endif	// IOBSERVER_DEFINED
