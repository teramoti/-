#include "Time.h"


Time::Time()
{
}


Time::~Time()
{
}

void Time::Update(float &timer)
{
	m_time = timer;

	countDown();

	if (m_flag==true)
	{
		m_time += 1.7f;
	}
	else
	{
		m_time = m_time;
	}

}

void Time::countDown()
{
	m_count--;
}

void Time::SetCount(float count)
{
	m_count = count;
}

float Time::GetCount()
{
	return m_count;
}

void Time::SetFlag(bool flag)
{
	m_flag = flag;
}

bool Time::GetFlag()
{
	return m_flag;
}

void Time::SetTime(float time)
{
	m_time = time;
}

float Time::GetTime()
{
	return m_time;
}


