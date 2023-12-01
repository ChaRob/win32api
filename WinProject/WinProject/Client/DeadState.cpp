#include "pch.h"
#include "DeadState.h"

DeadState::DeadState() :
	State(MON_STATE::DEAD)
{
}

DeadState::~DeadState()
{
}

void DeadState::Update()
{
}

void DeadState::Enter()
{
}

void DeadState::Exit()
{
}
