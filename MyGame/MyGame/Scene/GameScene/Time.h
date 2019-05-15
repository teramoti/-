#pragma once
class Time
{
public:
	Time();
	~Time();

	void Update(float &timer);

	void SetTime(float time);
	float GetTime();

	void SetCount(float count);
	float GetCount();

	void SetFlag(bool flag);
	bool GetFlag();

	void countDown();

private:
	//カウントダウン
	float m_count = 180;
	//時間
	float m_time = 0;

	//
	bool m_flag = true;
};
