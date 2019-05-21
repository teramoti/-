#include "GameSaveData.h"


void GameSaveData::SetGoal1Time(float goalTime)
{
	m_nowScore[0] = goalTime;
}

float GameSaveData::GetGoal1Time()
{
	return m_nowScore[0];
}
float GameSaveData::GetHigh1Time()
{
	m_Flag = false;

	if (m_nowScore[0] <= m_v[0])
	{
		m_v[0] = m_nowScore[0];
		m_HighTime[0] = m_v[0];
		m_Flag = true;
		return m_HighTime[0];
	}
	return m_v[0];
}

int GameSaveData::GetRank()
{
	return m_goalRank;
}
void GameSaveData::SetStageNum(int num)
{
	m_stageNum = num;
}

void GameSaveData::SetLoadName(std::wstring name)
{
	m_name = name;
}

void GameSaveData::SetLoadColName(std::wstring name)
{
	m_colName = name;
}

void GameSaveData::SetLoadEnemyName(std::wstring name)
{
	m_enemyName = name;
}

void GameSaveData::SetRank(int num)
{
	m_goalRank = num;
}
