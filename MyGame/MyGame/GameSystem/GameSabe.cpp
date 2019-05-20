#include "GameSabe.h"


/// <summary>
/// コンストラクタ
/// </summary>
System::GameSabe::GameSabe()
{

}
void System::GameSabe::SetGoalTime(float goalTime)
{
	m_goalTime = goalTime;
}

float System::GameSabe::GetGoalTime()
{
	return m_goalTime;
}