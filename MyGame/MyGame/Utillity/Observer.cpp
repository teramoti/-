#include "Observer.h"

Observer::Observer(MyAirPlane* player)
{
	m_player = player;

}

void Observer::Update(Subject* subject)
{
	m_subject = subject->GetSubject();

	m_player->AddCoin();
}
