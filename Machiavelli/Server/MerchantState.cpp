#include "MerchantState.h"


MerchantState::MerchantState()
{
}


MerchantState::~MerchantState()
{
}

void MerchantState::Init(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	int gold = game->RemoveGold(1);
	if (gold != -1) {
		player->AddGold(gold);
		player->GetClient()->writeline("You received 1 gold coin!");
	}

	int greenBuildings = 0;
	for (size_t i = 0, blen = player->GetBuildings()->Size(); i < blen; ++i) {
		if (player->GetBuildings()->ShowCardByIndex(i).GetColor() == 2)
			greenBuildings++;
	}
	if (greenBuildings > 0) {
		int gold = game->RemoveGold(greenBuildings);
		if (gold != -1) {
			player->AddGold(gold);
			player->GetClient()->writeline("You receive 1 gold coin for each green building, " + std::to_string(gold) + " gold received!");
		}
	}
	else {
		player->GetClient()->writeline("You do not own any green buildings and therefor receive no gold");
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
	int choice = -1;
	while (choice != 4) {
		do {
			RenderChoices(player);
			choice = HandleChoice(player, game, 4);
		} while (choice == -1);
		HandleTurn(player, game, choice);
	}
}

void MerchantState::UseAbility(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}
