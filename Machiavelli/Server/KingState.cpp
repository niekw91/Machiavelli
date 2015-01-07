#include "KingState.h"


KingState::KingState()
{
}


KingState::~KingState()
{
}

void KingState::Init(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	// Crown the king
	game->GetOpponent(player)->SetCrown(false);
	player->SetCrown(true);

	// Receive gold for player color buildings
	int playercolor = Game::Color::YELLOW;
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

void KingState::Cleanup(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void KingState::HandleEvents(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void KingState::Update(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	Render(player, "King");
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

void KingState::UseAbility(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	player->GetClient()->writeline("King Character Traits:");
	player->GetClient()->writeline("  - A king receives 1 gold piece for every gold building he has built.");
	player->GetClient()->writeline("  - A King also gets to start at the beginning of a round.");
}