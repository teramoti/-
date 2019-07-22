#include "Observer.h"

Observer::Observer(const std::string & name, MyAirPlane* player)
{
	m_player = player;

}

void Observer::Update(DirectX::SimpleMath::Vector3 & pos)
{
	m_player->AddCoin();
}
