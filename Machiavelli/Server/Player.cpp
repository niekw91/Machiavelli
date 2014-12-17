#include "Player.h"
#include "Socket.h"
#include "Game.h"


Player::Player(shared_ptr<Socket> &client, shared_ptr<Game> &game) {
	_client = client;
	_game = game;
	_hasCrown = false;
}


Player::~Player()
{
}

void Player::SetCrown(bool crown)
{
	_hasCrown = crown;
}

bool Player::HasCrown()
{
	return _hasCrown;
}
