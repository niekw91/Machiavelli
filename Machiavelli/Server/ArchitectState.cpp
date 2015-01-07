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
	ResetChoices(player, game, "Architect");
	int choice = -1;
	while (choice != GetNumberOfChoices() - 1) {
		do {
			RenderChoices(player);
			choice = HandleChoice(player, game, GetNumberOfChoices() - 1);
		} while (choice == -1);
		HandleTurn(player, game, choice);
	}
}

void ArchitectState::UseAbility(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}
