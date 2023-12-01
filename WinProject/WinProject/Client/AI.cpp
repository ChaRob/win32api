#include "pch.h"
#include "AI.h"

AI::AI():
	m_owner(nullptr), m_curState(nullptr)
{
}

AI::~AI()
{
	SafeDeleteMap(m_mapState);
}

void AI::Update()
{
	m_curState->Update();
}

void AI::AddState(State* _state)
{
	State* pState = GetState(_state->GetType());
	assert(!pState);

	m_mapState.insert(make_pair(_state->GetType(), _state));
	_state->m_AI = this;
}

State* AI::GetState(MON_STATE _state)
{
	map<MON_STATE, State*>::iterator iter = m_mapState.find(_state);
	if (iter == m_mapState.end()) {
		return nullptr;
	}
	return iter->second;
}

void AI::SetState(MON_STATE _state)
{
	m_curState = GetState(_state);
	assert(m_curState);
}

void AI::ChangeState(MON_STATE _state)
{
	State* nextState = GetState(_state);
	assert(nextState != m_curState);

	m_curState->Exit();
	m_curState = nextState;
	m_curState->Enter();
}
