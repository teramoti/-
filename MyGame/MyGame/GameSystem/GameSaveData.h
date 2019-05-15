#pragma once
#include <string>
#include "../Utillity/SingletonBase.h"

class GameSaveData : public Utility::SingletonBase<GameSaveData>
{
public:
	void SetGoal1Time(float goalTime);
public:

	float GetGoal1Time();
	float GetHigh1Time();
	int GetRank();

	void SetStageNum(int num);
	void SetLoadName(std::wstring name);
	void SetLoadColName(std::wstring name);
	void SetLoadEnemyName(std::wstring name);

	void SetRank(int num);
public:

	std::wstring& GetLoadName()
	{
		return m_name;

	}


	std::wstring& GetLoadColName()
	{
		return m_colName;

	}
	std::wstring& SetLoadEnemyName()
	{
		return m_enemyName;
	}

	bool GetFlag()
	{
		return m_Flag;
	}

	int& GetStage()
	{
		return m_stageNum;
	}

	private:

	float m_goalTime[3];
	float m_HighTime[3];
	float m_nowScore[3];
	float m_v[3] = {5999,5999,5999};

	int m_stageNum;//ステージの番号用
	int m_goalRank;
	std::wstring m_name;
	std::wstring m_colName;
	std::wstring m_enemyName;

	bool m_Flag;
};

