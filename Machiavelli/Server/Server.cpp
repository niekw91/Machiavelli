#include "Server.h"
#include "ServerConfig.h"
#include "Socket.h"
#include "Sync_queue.h"
#include "ClientCommand.h"

#include <thread>
#include <iostream>
#include <exception>
//#include <memory>


using namespace std;

static Sync_queue<ClientCommand> syncQueue;

void Server::Start(shared_ptr<Game> &game) {
	// start command consumer thread
	thread consumer{ Server::Consume, game };
	consumer.detach(); // detaching is usually ugly, but in this case the right thing to do

	// create a server socket
	ServerSocket server(ServerConfig::tcp_port);

	while (true) {
		try {
			// wait for connection from client; will create new socket
			cerr << "Server: listening" << '\n';
			shared_ptr<Socket> client = nullptr;

			while ((client = server.accept()) != nullptr) {
				// communicate with client over new socket in separate thread
				thread handler{ Server::HandleClient, client, game };

				// Add new client to game
				game->AddPlayer(client);

				handler.detach(); // detaching is usually ugly, but in this case the right thing to do
				cerr << "Server: listening again" << '\n';
			}
		}
		catch (const exception& ex) {
			cerr << ex.what() << ", resuming..." << '\n';
		}
	}
}

void Server::HandleClient(shared_ptr<Socket> &socket, shared_ptr<Game> &game) {
	shared_ptr<Socket> client{ socket };

	while (true) {
		try {
			// read first line of request
			string cmd = client->readline();
			cerr << "client (" << client->get() << ") said: " << cmd << '\n';

			if (cmd == "quit") {
				client->write("Bye!\n");
				break; 
			}

			ClientCommand command{ cmd, client };
			syncQueue.put(command);

		}
		catch (const exception& ex) {
			client->write("ERROR: ");
			client->write(ex.what());
			client->write("\n");
		}
		catch (...) {
			client->write("ERROR: something went wrong during handling of your request. Sorry!\n");
		}
	}
}

void Server::Consume(shared_ptr<Game> &game) {
	while (true) {
		ClientCommand command;
		syncQueue.get(command); // will block here unless there still are command objects in the queue
		shared_ptr<Socket> client{ command.get_client() };
		if (client) {
			try {
				game->AddCommand(command);
			}
			catch (const exception& ex) {
				client->write("Sorry, ");
				client->write(ex.what());
				client->write("\n");
			}
			catch (...) {
				client->write("Sorry, something went wrong during handling of your request.\n");
			}
			client->write(ServerConfig::prompt);
		}
		else {
			cerr << "trying to handle command for client who has disappeared...\n";
		}
	}
}
