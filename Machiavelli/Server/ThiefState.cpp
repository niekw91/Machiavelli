#include "ThiefState.h"


ThiefState::ThiefState()
{
}


ThiefState::~ThiefState()
{
}

void ThiefState::Init(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void ThiefState::Cleanup(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void ThiefState::HandleEvents(shared_ptr<Player> &player, shared_ptr<Game> &game)
{

}

void ThiefState::Update(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	Render(player, "Thief");
	ResetChoices();
	int choice = -1;
	while (choice != GetNumberOfChoices()) {
		do {
			RenderChoices(player);
			choice = HandleChoice(player, game, GetNumberOfChoices() - 1);
		} while (choice == -1);
		HandleTurn(player, game, choice);
	}
}

void ThiefState::UseAbility(shared_ptr<Player> &player, shared_ptr<Game> &game)
{
	player->GetClient()->writeline("Which character do you want to steal from:");
	player->GetClient()->writeline("  [0] Wizard");
	player->GetClient()->writeline("  [1] King");
	player->GetClient()->writeline("  [2] Bishop");
	player->GetClient()->writeline("  [3] Merchant");
	player->GetClient()->writeline("  [4] Architect");
	player->GetClient()->writeline("  [5] Warlord");

	Game::Character character = Game::LAST_CHARACTER;
	do {
		int choice = -1;
		do {
			choice = HandleChoice(player, game, 6);
		} while (choice == -1);	

		switch (choice)
		{
		case 0:	
			character = Game::WIZARD; 
			if (game->HasBeenKilled(character))
				player->GetClient()->writeline("You can't steal from a character that's been killed!");
			break;
		case 1: 
			character = Game::KING;
			if (game->HasBeenKilled(character))
				player->GetClient()->writeline("You can't steal from a character that's been killed!"); 
			break;
		case 2: 
			character = Game::BISHOP; 
			if (game->HasBeenKilled(character))
				player->GetClient()->writeline("You can't steal from a character that's been killed!"); 
			break;
		case 3: 
			character = Game::MERCHANT;
			if (game->HasBeenKilled(character))
				player->GetClient()->writeline("You can't steal from a character that's been killed!"); 
			break;
		case 4: 
			character = Game::ARCHITECT;
			if (game->HasBeenKilled(character))
				player->GetClient()->writeline("You can't steal from a character that's been killed!"); 
			break;
		case 5: 
			character = Game::WARLORD;
			if (game->HasBeenKilled(character))
				player->GetClient()->writeline("You can't steal from a character that's been killed!"); 
			break;
		default: break;
		}
	} while (character == Game::LAST_CHARACTER && !game->HasBeenKilled(character));

	game->StealFrom(character);
}
