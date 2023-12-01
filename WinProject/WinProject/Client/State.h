#pragma once
#include "AI.h"

class AI;
class Monster;

class State
{
	friend class AI;
public:
	State(MON_STATE _state);
	virtual ~State();

	virtual void Update() = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;

private:
	AI* m_AI;
	MON_STATE m_state;

public:
	AI* GetAI() { return m_AI; }
	MON_STATE GetType() { return m_state; }
	Monster* GetOwner();
};

