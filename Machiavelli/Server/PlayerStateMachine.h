#pragma once
#include <memory>
#include <vector>

class Player;
class PlayerState;
class Game;

using namespace std;

class PlayerStateMachine
{
public:
	PlayerStateMachine();
	~PlayerStateMachine();

	void Init(shared_ptr<Player> &player, shared_ptr<Game> &game);
	void Cleanup(shared_ptr<Player> &player, shared_ptr<Game> &game);

	void ChangeState(shared_ptr<Player> &player, shared_ptr<Game> &game, shared_ptr<PlayerState> &state);
	void PushState(shared_ptr<Player> &player, shared_ptr<Game> &game, shared_ptr<PlayerState> &state);
	void PopState(shared_ptr<Player> &player, shared_ptr<Game> &game);

	void HandleEvents(shared_ptr<Player> &player, shared_ptr<Game> &game);
	void Update(shared_ptr<Player> &player, shared_ptr<Game> &game);
private:
	vector<shared_ptr<PlayerState>> _states;
};