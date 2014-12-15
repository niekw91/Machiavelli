#pragma once
#include <vector>
#include <memory>

using namespace std;

// Forward declaration
class Player;
class GameStateManager;

class Game : public enable_shared_from_this<Game>
{
public:
	Game();
	virtual ~Game();

	void Init();
	void Cleanup();

	void Start();
	void Stop();

	void HandleEvents(shared_ptr<Game> &game);
	void Update(shared_ptr<Game> &game);

	shared_ptr<GameStateManager> &GetStateManager() { return _stateManager; }

private:
	shared_ptr<GameStateManager> _stateManager;

	bool _running;
};

