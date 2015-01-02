#include "WarlordState.h"


WarlordState::WarlordState()
{
}


WarlordState::~WarlordState()
{
}

void WarlordState::Init(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	int redBuildings = 0;
	for (size_t i = 0, blen = player->GetBuildings()->Size(); i < blen; ++i) {
		if (player->GetBuildings()->ShowCardByIndex(i).GetColor() == 4)
			redBuildings++;
	}
	if (redBuildings > 0) {
		int gold = game->RemoveGold(redBuildings);
		if (gold != -1) {
			player->AddGold(gold);
			player->GetClient()->writeline("You receive 1 gold coin for each red building, " + std::to_string(gold) + " gold received!");
		}
	}
	else {
		player->GetClient()->writeline("You do not own any red buildings and therefor receive no gold");
	}
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

void WarlordState::UseAbility(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	if (game->GetOpponent(player)->GetBuildings()->Size() >= 8) {
		player->GetClient()->writeline("Your opponent has built 8 or more buildings, you are not allowed to destroy his buildings!");
	}
	else if (game->GetOpponent(player)->HasCharacterCard("Bishop")) {
		player->GetClient()->writeline("Your opponent has the bishop card, you are not allowed to destroy his buildings!");
	}
	else {
		// Print opponent cards
		LookAtOpponent(player, game);

		player->GetClient()->writeline("Which building do you want to destroy?");

		int choice = -1;
		do {
			choice = HandleChoice(player, game, player->GetBuildings()->Size() - 1);
		} while (choice == -1);

		BuildingCard destroy = game->GetOpponent(player)->GetBuildings()->ShowCardByIndex(choice);
		if (destroy.GetValue() == 1)
			game->GetOpponent(player)->DestroyByIndex(choice);
		else  {
			int cost = destroy.GetValue() - 1;
			if (player->GetGoldAmount() >= cost) {
				// Player has enough gold to destroy building
				player->RemoveGold(cost);
				game->AddGold(cost);
				game->GetOpponent(player)->DestroyByIndex(choice);
				player->GetClient()->writeline("Building destroyed!");
			}
			else {
				// Not enough gold to destroy this building
				player->GetClient()->writeline("Not enough gold available to destroy this building!");
			}
		}
	}
}