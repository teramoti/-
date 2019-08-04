
#include "Subject.h"

void Subject::Attach(Observer* shop)
{
	m_observerVector.push_back(shop);
}

void Subject::Detach(Observer* shop)
{
	m_observerVector.erase(std::remove(m_observerVector.begin(), m_observerVector.end(), shop), m_observerVector.end());
}

// ’Ê’m‚·‚é
void Subject::Notify(DirectX::SimpleMath::Vector3& pos)
{
	std::vector<Observer*>::iterator iter;
	for (iter = m_observerVector.begin(); iter != m_observerVector.end(); iter++)
	{
		if (*iter != 0)
		{
			(*iter)->Update(this);
		}
	}
}
