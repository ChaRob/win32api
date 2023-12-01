#pragma once
#include "State.h"

class IdleState : public State
{
public:
	IdleState();
	~IdleState();

	virtual void Update();
	virtual void Enter();
	virtual void Exit();

private:

};

