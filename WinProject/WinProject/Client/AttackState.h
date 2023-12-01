#pragma once
#include "State.h"
class AttackState : public State
{
public:
	AttackState();
	~AttackState();

	virtual void Update();
	virtual void Enter();
	virtual void Exit();
};

