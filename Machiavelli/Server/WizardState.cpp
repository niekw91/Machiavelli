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

void WizardState::UseAbility(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	player->GetClient()->writeline("Use magic to:");
	player->GetClient()->writeline("  [0] Switch your and your opponent's cards");
	player->GetClient()->writeline("  [1] Discard from hand and draw the same amount of cards");
	
	shared_ptr<CardStack<BuildingCard>> buildingCards = player->GetBuildingCards();
	auto tmp(buildingCards);
	int numberOfHandCards = 0;
	int numberOfDiscardedCards = 0;
	int choice = -1;
	do {
		choice = HandleChoice(player, game, 2);
	} while (choice == -1);

	switch (choice)
	{
	case 0:
		//player->GetBuildingCards().swap(game->GetOpponent(player)->GetBuildingCards());
		player->SetBuildingCards(game->GetOpponent(player)->GetBuildingCards());
		game->GetOpponent(player)->SetBuildingCards(tmp);
		break;
	case 1:
		choice = -1;
		do{
		// Show cards in hand
		player->GetClient()->writeline("Cards in hand:");
		for (size_t i = 0, blen = buildingCards->Size(); i < blen; ++i) {
			std::string name = buildingCards->ShowCardByIndex(i).GetName();
			std::string color = std::to_string(buildingCards->ShowCardByIndex(i).GetColor());
			std::string value = std::to_string(buildingCards->ShowCardByIndex(i).GetValue());
			player->GetClient()->writeline("  [" + to_string(i) + "] " + name + "(" + color + "," + value + ")");
		}
		numberOfHandCards = buildingCards->Size();
		player->GetClient()->writeline("  [" + to_string(numberOfHandCards) + "] Done");

		// Select cards to be discarded
		player->GetClient()->writeline("\r\nSelect card to be discarded:");
			do {
				choice = HandleChoice(player, game, buildingCards->Size());
			} while (choice == -1);
			// Discard cards from hand
			if (choice != buildingCards->Size()) {
				player->RemoveBuildingCard(choice);
				++numberOfDiscardedCards;
			}
		} while (choice == -1 || choice != numberOfHandCards);

		// Draw same number of cards from deck
		player->GetClient()->writeline("\r\nYou've drawn " + to_string(numberOfDiscardedCards) + " card(s) from deck:");
		for (int i = 0, blen = numberOfDiscardedCards; i < blen; ++i) {
			std::string name = player->DrawCard().GetName();
			std::string color = std::to_string(player->DrawCard().GetColor());
			std::string value = std::to_string(player->DrawCard().GetValue());
			player->GetClient()->writeline("  - " + name + "(" + color + "," + value + ")");
		}
		break;
	default:
		break;
	}
}