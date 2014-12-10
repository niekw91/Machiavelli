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
	GameStateManager(Game &game);
	~GameStateManager();

	void Init(Game &game);
	void Cleanup(Game &game);

	void ChangeState(Game &game, GameState &state);
	void PushState(Game &game, GameState &state);
	void PopState(Game &game);

	void HandleEvents(Game &game);
	void Update(Game &game);

private:
	vector<unique_ptr<GameState>> _states;
};

