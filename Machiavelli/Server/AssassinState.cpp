#include "AssassinState.h"


AssassinState::AssassinState()
{
}


AssassinState::~AssassinState()
{
}

void AssassinState::Init(shared_ptr<Player> &player)
{

}

void AssassinState::Cleanup(shared_ptr<Player> &player)
{

}

void AssassinState::HandleEvents(shared_ptr<Player> &player)
{

}

void AssassinState::Update(shared_ptr<Player> &player)
{
	Write(player, "Assassin");
}