#include "BishopState.h"


BishopState::BishopState()
{
}


BishopState::~BishopState()
{
}

void BishopState::Init(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	int blueBuildings = 0;
	for (size_t i = 0, blen = player->GetBuildings()->Size(); i < blen; ++i) {
		if (player->GetBuildings()->ShowCardByIndex(i).GetColor() == 3)
			blueBuildings++;
	}
	if (blueBuildings > 0) {
		int gold = game->RemoveGold(blueBuildings);
		if (gold != -1) {
			player->AddGold(gold);
			player->GetClient()->writeline("You receive 1 gold coin for each blue building, " + std::to_string(gold) + " gold received!");
		}
	}
	else {
		player->GetClient()->writeline("You do not own any blue buildings and therefor receive no gold");
	}
}

void BishopState::Cleanup(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void BishopState::HandleEvents(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void BishopState::Update(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	Render(player, "Bishop");
	int choice = -1;
	while (choice != 4) {
		do {
			RenderChoices(player);
			choice = HandleChoice(player, game, 4);
		} while (choice == -1);
		HandleTurn(player, game, choice);
	}
}

void BishopState::UseAbility(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}