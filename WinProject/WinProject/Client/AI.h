#pragma once
#include "Monster.h"
#include "State.h"

class State;
class Monster;

class AI
{
	friend class Monster;
public:
	AI();
	~AI();

private:
	map<MON_STATE, State*> m_mapState;
	Monster* m_owner;
	State* m_curState;

public:
	void Update();
	void AddState(State* _state);
	State* GetState(MON_STATE _state);
	void SetState(MON_STATE _state);
	Monster* GetOwnerMonster() { return m_owner; }
	void ChangeState(MON_STATE _state);
};

