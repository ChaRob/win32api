#include "pch.h"
#include "TraceState.h"
#include "SceneMgr.h"
#include "CScene.h"
#include "Player.h"
#include "Monster.h"
#include "CTimeMgr.h"

TraceState::TraceState() :
	State(MON_STATE::TRACE)
{
}

TraceState::~TraceState()
{
}

void TraceState::Update()
{
	// 타겟팅 된 플레이어를 쫓아간다.
	Player* player = (Player*)SceneMgr::GetInstance()->GetCurScene()->GetPlayer();
	Vector2 playerPos = player->GetPos();

	Monster* monster = GetOwner();
	Vector2 monPos = monster->GetPos();

	float speed = monster->GetMonsterInfo().speed;
	Vector2 dir = (playerPos - monPos).Normalize();
	monPos += dir * speed * DeltaTimef;

	monster->SetPos(monPos);
}

void TraceState::Enter()
{
}

void TraceState::Exit()
{
}
