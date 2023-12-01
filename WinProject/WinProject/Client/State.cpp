#include "pch.h"
#include "State.h"
#include "Monster.h"
#include "AI.h"

State::State(MON_STATE _state):
	m_AI(nullptr), m_state(_state)
{
}

State::~State()
{
}

Monster* State::GetOwner()
{
	return m_AI->GetOwnerMonster();
}
