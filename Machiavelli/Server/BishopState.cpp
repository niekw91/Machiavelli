#include "BishopState.h"


BishopState::BishopState()
{
}


BishopState::~BishopState()
{
}

void BishopState::Init(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void BishopState::Cleanup(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void BishopState::HandleEvents(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void BishopState::Update(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	Render(player, "Bishop");
	int choice = -1;
	while (choice != 4) {
		do {
			choice = HandleChoice(player, game, 4);
		} while (choice == -1);
		HandleTurn(player, game, choice);
	}
}

void BishopState::UseAbility(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}