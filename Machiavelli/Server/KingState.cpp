#include "KingState.h"


KingState::KingState()
{
}


KingState::~KingState()
{
}

void KingState::Init(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void KingState::Cleanup(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void KingState::HandleEvents(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void KingState::Update(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	Render(player, "King");
	int choice = -1;
	while (choice != 4) {
		do {
			RenderChoices(player);
			choice = HandleChoice(player, game, 4);
		} while (choice == -1);
		HandleTurn(player, game, choice);
	}
}

void KingState::UseAbility(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}