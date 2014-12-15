#pragma once
#include <memory>

class Socket;

using namespace std;

class Player
{
public:
	Player(shared_ptr<Socket> &socket);
	virtual ~Player();

	shared_ptr<Socket> GetClient() { return client; }
private:
	shared_ptr<Socket> client;
};

