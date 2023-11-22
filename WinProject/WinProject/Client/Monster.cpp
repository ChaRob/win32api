#include "pch.h"
#include "Monster.h"
#include "CTimeMgr.h"

Monster::Monster() :
	m_CenterPos(Vector2{ 0.f, 0.f }),
	m_fSpeed(100.f),
	m_MaxDistance(50.f),
	m_dir(1)
{
	CreateCollider();
}

Monster::~Monster()
{
}

void Monster::Update()
{
	Vector2 curPos = GetPos();
	curPos.x += DeltaTimef * m_fSpeed * m_dir;

	if (abs(m_CenterPos.x - curPos.x) >= m_MaxDistance) {
		curPos.x = m_CenterPos.x + m_MaxDistance * m_dir;
		m_dir *= -1;
	}

	SetPos(curPos);
}
