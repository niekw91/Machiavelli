#include "WarlordState.h"


WarlordState::WarlordState()
{
}


WarlordState::~WarlordState()
{
}

void WarlordState::Init(shared_ptr<Player> &player)
{

}

void WarlordState::Cleanup(shared_ptr<Player> &player)
{

}

void WarlordState::HandleEvents(shared_ptr<Player> &player)
{

}

void WarlordState::Update(shared_ptr<Player> &player)
{
	player->GetClient()->write("You are the: Warlord");
	player->GetClient()->write("Gold: " + std::to_string(player->GetGoldAmount()));
}
