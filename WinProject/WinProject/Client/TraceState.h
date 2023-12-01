#pragma once
#include "State.h"
class TraceState : public State
{
public:
	TraceState();
	~TraceState();

	virtual void Update();
	virtual void Enter();
	virtual void Exit();
};

