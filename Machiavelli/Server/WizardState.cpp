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
			RenderChoices(player);
			choice = HandleChoice(player, game, 4);
		} while (choice == -1);
		HandleTurn(player, game, choice);
	}
}

void WizardState::UseAbility(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	player->GetClient()->writeline("Use magic to:");
	player->GetClient()->writeline("  [0] Switch your and your opponent's cards");
	player->GetClient()->writeline("  [1] Discard from hand and draw the same amount of cards");
	
	int choice = -1;
	int discarded = 0;
	auto cards = player->GetBuildingCards();

	do {
		choice = HandleChoice(player, game, 2);
	} while (choice == -1);

	switch (choice)
	{
	case 0:
		player->GetBuildingCards().swap(game->GetOpponent(player)->GetBuildingCards());
		break;
	case 1:
		choice = -1;
		do {
			choice = HandleChoice(player, game, 2);
		} while (choice == -1);

		break;
	default:
		break;
	}
}