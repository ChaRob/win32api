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
	// player�� ��ġ�� üũ�ϰ�
	// ������ �ν� ���� �ȿ� ������ �������·� ��ȯ
	Player* player = (Player*)SceneMgr::GetInstance()->GetCurScene()->GetPlayer();
	Vector2 playerPos = player->GetPos();

	Monster* monster = GetOwner();
	Vector2 monsterPos = monster->GetPos();

	Vector2 diff = monsterPos - playerPos;
	
	// �÷��̾ ������ �νĹ��� ������ ����
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
