#include "WarlordState.h"


WarlordState::WarlordState()
{
}


WarlordState::~WarlordState()
{
}

void WarlordState::Init(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	// Receive gold for player color buildings
	int playercolor = Game::Color::RED;
	int playercolorbuildings = 0;
	auto buildings = player->GetBuildings();

	for (auto i = 0, ilen = buildings->Size(); i < ilen; ++i) {
		if (buildings->GetCardByIndex(i).GetColor() == playercolor)
			++playercolorbuildings;
	}
	if (playercolorbuildings > 0)
		player->AddGold(playercolorbuildings);
	else {
		player->GetClient()->writeline("You do not own any " + GetColor(playercolor) + " buildings and therefore receive no gold");
	}
	if (player->HasBuilding("School of Wizards")) {
		int gold = 1;
		player->AddGold(gold);
		player->GetClient()->writeline("You receive 1 gold coin for the School of Wizards, " + to_string(gold) + " gold received!");
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
	_endTurn = false;
	int choice = -1;
	while (!_endTurn) {
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
		if (destroy.GetName() == "Dungeon")
			player->GetClient()->writeline("A dungeon cannot be destroyed!");
		else {
			if (destroy.GetValue() == 1)
				game->GetOpponent(player)->DestroyByIndex(choice);
			else  {
				int cost = destroy.GetValue() - 1;
				if (player->GetGoldAmount() >= cost) {
					// Player has enough gold to destroy building
					player->RemoveGold(cost);
					game->AddGold(cost);
					BuildingCard card = game->GetOpponent(player)->GetBuildings()->GetCardByIndex(choice);
					game->AddBuildingCard(card);
					player->GetClient()->writeline("Building destroyed!");
				}
				else {
					// Not enough gold to destroy this building
					player->GetClient()->writeline("Not enough gold available to destroy this building!");
				}
			}
		}
	}
}