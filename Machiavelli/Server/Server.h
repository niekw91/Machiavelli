#pragma once
#include "Game.h"
#include <memory>

class Socket;

class Server
{
public:
	static void Start(shared_ptr<Game> &game);
	static void HandleClient(Socket* socket, shared_ptr<Game> &game);
	static void Consume(shared_ptr<Game> &game);
private:
	
};

