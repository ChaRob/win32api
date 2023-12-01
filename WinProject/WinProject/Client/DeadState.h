#pragma once
#include "State.h"
class DeadState : public State
{
public:
	DeadState();
	~DeadState();

	virtual void Update();
	virtual void Enter();
	virtual void Exit();
};

