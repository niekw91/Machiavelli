#include "WizardState.h"


WizardState::WizardState()
{
}


WizardState::~WizardState()
{
}

void WizardState::Init(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void WizardState::Cleanup(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void WizardState::HandleEvents(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void WizardState::Update(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	Render(player, "Wizard");
	int choice = -1;
	while (choice != 4) {
		do {
			choice = HandleChoice(player, game, 4);
		} while (choice == -1);
		HandleTurn(player, game, choice);
	}
}

void WizardState::UseAbility(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}