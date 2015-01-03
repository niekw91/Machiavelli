#include "AssassinState.h"
#include "GameStateManager.h"

AssassinState::AssassinState()
{
}


AssassinState::~AssassinState()
{
}

void AssassinState::Init(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void AssassinState::Cleanup(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void AssassinState::HandleEvents(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void AssassinState::Update(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	Render(player, "Assassin");
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

void AssassinState::UseAbility(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	player->GetClient()->writeline("You are allowed to assassinate one of the following players:");
	player->GetClient()->writeline("  0. Thief");
	player->GetClient()->writeline("  1. Wizard");
	player->GetClient()->writeline("  2. King");
	player->GetClient()->writeline("  3. Bishop");
	player->GetClient()->writeline("  4. Merchant");
	player->GetClient()->writeline("  5. Architect");
	player->GetClient()->writeline("  6. Warlord");

	int choice = -1;
	do {
		choice = HandleChoice(player, game, 6);
	} while (choice == -1);

	Game::Character character;
	switch (choice)
	{
	case 0: character = Game::THIEF; break;
	case 1: character = Game::WIZARD; break;
	case 2: character = Game::KING; break;
	case 3: character = Game::BISHOP; break;
	case 4: character = Game::MERCHANT; break;
	case 5: character = Game::ARCHITECT; break;
	case 6: character = Game::WARLORD; break;
	}

	game->KillCharacter(character);
}