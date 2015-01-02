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
	ResetChoices(player, game);
	int choice = -1;
	while (choice != GetNumberOfChoices()) {
		do {
			RenderChoices(player);
			choice = HandleChoice(player, game, GetNumberOfChoices() - 1);
		} while (choice == -1);
		HandleTurn(player, game, choice);
	}
}

void KingState::UseAbility(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}