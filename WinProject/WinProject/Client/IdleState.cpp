#include "pch.h"
#include "IdleState.h"
#include "SceneMgr.h"
#include "CScene.h"
#include "Player.h"
#include "Monster.h"

IdleState::IdleState():
	State(MON_STATE::IDLE)
{
}

IdleState::~IdleState()
{
}

void IdleState::Update()
{
	// player의 위치를 체크하고
	// 몬스터의 인식 범위 안에 들어오면 추적상태로 전환
	Player* player = (Player*)SceneMgr::GetInstance()->GetCurScene()->GetPlayer();
	Vector2 playerPos = player->GetPos();

	Monster* monster = GetOwner();
	Vector2 monsterPos = monster->GetPos();

	Vector2 diff = monsterPos - playerPos;
	
	// 플레이어가 몬스터의 인식범위 안으로 진입
	if (diff.Length() < monster->GetMonsterInfo().recogRange) {
		ChangeAIState(GetAI(), MON_STATE::TRACE);
	}
}

void IdleState::Enter()
{
}

void IdleState::Exit()
{
}
