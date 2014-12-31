#include "WarlordState.h"


WarlordState::WarlordState()
{
}


WarlordState::~WarlordState()
{
}

void WarlordState::Init(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void WarlordState::Cleanup(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void WarlordState::HandleEvents(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void WarlordState::Update(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	Render(player, "Warlord");
	int choice = -1;
	while (choice != 4) {
		do {
			RenderChoices(player);
			choice = HandleChoice(player, game, 4);
		} while (choice == -1);
		HandleTurn(player, game, choice);
	}
}

void WarlordState::UseAbility(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}