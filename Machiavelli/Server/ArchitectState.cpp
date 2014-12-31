#include "ArchitectState.h"


ArchitectState::ArchitectState()
{
}


ArchitectState::~ArchitectState()
{
}

void ArchitectState::Init(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void ArchitectState::Cleanup(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void ArchitectState::HandleEvents(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void ArchitectState::Update(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	Render(player, "Architect");
	int choice = -1;
	while (choice != 4) {
		do {
			RenderChoices(player);
			choice = HandleChoice(player, game, 4);
		} while (choice == -1);
		HandleTurn(player, game, choice);
	}
}

void ArchitectState::UseAbility(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}
