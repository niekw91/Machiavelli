#include "Game.h"
#include "Player.h"

Game::Game() {
}


Game::~Game() {
}

void Game::AddPlayer() {
	_players.push_back(new Player());
}

int Game::GetPlayerCount() {
	return _players.size();
}
