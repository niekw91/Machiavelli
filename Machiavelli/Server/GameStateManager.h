#pragma once
#include <vector>
#include <memory>

using namespace std;

// Forward declaration
class Game;
class GameState;

class GameStateManager
{
public:
	GameStateManager();
	~GameStateManager();

	void Init(shared_ptr<Game> &game);
	void Cleanup(shared_ptr<Game> &game);

	void ChangeState(shared_ptr<Game> &game, shared_ptr<GameState> &state);
	void PushState(shared_ptr<Game> &game, shared_ptr<GameState> &state);
	void PopState(shared_ptr<Game> &game);

	void HandleEvents(shared_ptr<Game> &game);
	void Update(shared_ptr<Game> &game);

private:
	vector<shared_ptr<GameState>> _states;
};

