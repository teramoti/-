#pragma once

#include "../Utillity/SingletonBase.h"


namespace System
{
	class GameSabe : public Utility::SingletonBase<GameSabe>
	{
	public:

		friend Utility::SingletonBase<GameSabe>;
	private:
		GameSabe();

	public:
		void SetGoalTime(float goalTime);
		float GetGoalTime();

		int& GetData()
		{
			return m_data;
		}

		void SetData(int& data)
		{
			this->m_data = data;
		}

	private:
		int m_data;
		float m_goalTime;
	};
}