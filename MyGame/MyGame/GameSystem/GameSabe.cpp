#include "GameSabe.h"
using namespace System;

/// <summary>
/// �R���X�g���N�^
/// </summary>
System::GameSabe::GameSabe()
{

}
void GameSabe::SetGoalTime(float goalTime)
{
	m_goalTime = goalTime;
}

float GameSabe::GetGoalTime()
{
	return m_goalTime;
}