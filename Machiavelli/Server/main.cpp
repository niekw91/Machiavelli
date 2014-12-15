using namespace std;
#include "Game.h"

int main(int argc, const char * argv[])
{
	// Create game
	auto game = make_shared<Game>();

	// Initialize game
	game->Init();

	// Start game
	game->Start();

	// Cleanup game
	game->Cleanup();
    
    return 0;
}