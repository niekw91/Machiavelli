using namespace std;
#include "Game.h"

int main(int argc, const char * argv[])
{
	// Create game
	auto game = make_shared<Game>();

	// Initialize game
	game->Init(game);

	// Start game
	game->Start(game);

	// Cleanup game
	game->Cleanup();

	//start_server();
    
    return 0;
}