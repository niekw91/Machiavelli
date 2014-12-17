#pragma once
#include <memory>

class Socket;
class Game;

using namespace std;

class Player
{
public:
	Player(shared_ptr<Socket> &socket, shared_ptr<Game> &game);
	virtual ~Player();

	shared_ptr<Socket> GetClient() { return _client; }

	void SetCrown(bool crown);
	bool HasCrown();
private:
	shared_ptr<Socket> _client;
	shared_ptr<Game> _game;

	bool _hasCrown;
};

