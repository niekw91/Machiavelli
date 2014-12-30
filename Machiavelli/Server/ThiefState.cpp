#include "ThiefState.h"


ThiefState::ThiefState()
{
}


ThiefState::~ThiefState()
{
}

void ThiefState::Init(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void ThiefState::Cleanup(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void ThiefState::HandleEvents(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void ThiefState::Update(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	Render(player, "Thief");
	int choice = -1;
	while (choice != 4) {
		do {
			choice = HandleChoice(player, game, 4);
		} while (choice == -1);
		HandleTurn(player, game, choice);
	}
}

void ThiefState::UseAbility(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}
