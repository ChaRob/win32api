#pragma once
#include "CObject.h"
#include "AI.h"
#include "State.h"

class AI;

struct MonsterInfo {
	float hp;
	float speed;
	float recogRange;
	float attackRange;
	float attackDamage;
};

class Monster : public CObject
{
	friend class MonFactory;
public:
	Monster();
	~Monster();
	virtual void Update();
	Monster* Clone() { return new Monster(*this); }

private:
	//Vector2 m_CenterPos;
	/*float m_MaxDistance;
	int m_dir;*/
	MonsterInfo monsterInfo;
	AI* m_ai;

public:
	float GetSpeed() { return monsterInfo.speed; }
	void SetSpeed(float _speed) { monsterInfo.speed = _speed; }
	//void SetCenterPos(Vector2 _vPos) { m_CenterPos = _vPos; }
	//void SetMaxDistance(float _dis) { m_MaxDistance = _dis; }

	virtual void OnCollision(Collider* _pOther);
	virtual void OnCollisionEnter(Collider* _pOther);
	virtual void OnCollisionExit(Collider* _pOther);

	void SetAI(AI* _ai);
	MonsterInfo GetMonsterInfo() { return monsterInfo; }

private:
	void SetMonInfo(const MonsterInfo& _info) { monsterInfo = _info; }
};

