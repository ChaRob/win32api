#include "pch.h"
#include "Monster.h"
#include "CTimeMgr.h"
#include "Collider.h"

Monster::Monster() :
	//m_CenterPos(Vector2{ 0.f, 0.f }),
	//m_MaxDistance(50.f),
	//m_dir(1),
	monsterInfo{},
	m_ai(nullptr)
{
	CreateCollider();
	GetCollider()->SetSize(Vector2{ 40.f, 40.f });
}

Monster::~Monster()
{
	if (m_ai != nullptr) {
		delete m_ai;
	}
}

void Monster::Update()
{
	m_ai->Update();
	/*Vector2 curPos = GetPos();
	curPos.x += DeltaTimef * m_fSpeed * m_dir;

	if (abs(m_CenterPos.x - curPos.x) >= m_MaxDistance) {
		curPos.x = m_CenterPos.x + m_MaxDistance * m_dir;
		m_dir *= -1;
	}

	SetPos(curPos);*/
}

void Monster::OnCollision(Collider* _pOther)
{
}

void Monster::OnCollisionEnter(Collider* _pOther)
{
	CObject* pOtherObj = _pOther->GetOwnerObject();
	if (pOtherObj->GetName() == L"PlayerMissle") {

		monsterInfo.hp--;
		if (monsterInfo.hp <= 0) {
			DeleteObejct(this);
		}
	}
}

void Monster::OnCollisionExit(Collider* _pOther)
{
}

void Monster::SetAI(AI* _ai)
{
	m_ai = _ai;
	_ai->m_owner = this;
}
