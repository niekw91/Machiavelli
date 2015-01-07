#include "MerchantState.h"


MerchantState::MerchantState()
{
}


MerchantState::~MerchantState()
{
}

void MerchantState::Init(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	TakeGold(player, game, 1);

	// Receive gold for player color buildings
	int playercolor = Game::Color::GREEN;
	int playercolorbuildings = 0;
	auto buildings = player->GetBuildings();

	for (auto i = 0, ilen = buildings->Size(); i < ilen; ++i) {
		if (buildings->ShowCardByIndex(i).GetColor() == playercolor)
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

void MerchantState::Cleanup(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void MerchantState::HandleEvents(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void MerchantState::Update(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	Render(player, "Merchant");
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

void MerchantState::UseAbility(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}
