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
	//�J�E���g�_�E��
	float m_count = 180;
	//����
	float m_time = 0;

	//
	bool m_flag = true;
};
