#include "pch.h"
#include "MonFactory.h"
#include "Monster.h"
#include "AI.h"
#include "IdleState.h"
#include "TraceState.h"

Monster* MonFactory::CreateMonster(MON_TYPE _type, Vector2 _pos)
{
	Monster* mon = nullptr;
	AI* monAI = nullptr;
	MonsterInfo info = {};

	switch (_type)
	{
	case MON_TYPE::NORMAL:
		mon = new Monster;
		mon->SetPos(_pos);

		info.hp = 10.f;
		info.speed = 50.f;
		info.recogRange = 300.f;
		info.attackDamage = 5.f;
		info.attackRange = 100.f;

		mon->SetMonInfo(info);

		monAI = new AI;
		monAI->AddState(new IdleState);
		monAI->AddState(new TraceState);
		monAI->SetState(MON_STATE::IDLE);
		mon->SetAI(monAI);

		break;
	case MON_TYPE::RANGE:
		break;
	default:
		break;
	}
	return mon;
}
