#pragma once
#include <memory>
#include <vector>

class Player;
class PlayerState;

using namespace std;

class PlayerStateMachine
{
public:
	PlayerStateMachine();
	~PlayerStateMachine();

	void Init(shared_ptr<Player> &player);
	void Cleanup(shared_ptr<Player> &player);

	void ChangeState(shared_ptr<Player> &player, shared_ptr<PlayerState> &state);
	void PushState(shared_ptr<Player> &player, shared_ptr<PlayerState> &state);
	void PopState(shared_ptr<Player> &player);

	void HandleEvents(shared_ptr<Player> &player);
	void Update(shared_ptr<Player> &player);
private:
	vector<shared_ptr<PlayerState>> _states;
};