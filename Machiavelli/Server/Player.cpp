#include "Player.h"
#include "Socket.h"


Player::Player(shared_ptr<Socket> &client) {
	this->client = client;
}


Player::~Player()
{
}
