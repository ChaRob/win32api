#include "pch.h"
#include "Missile.h"
#include "CTimeMgr.h"

Missile::Missile() : m_dir(Vector2{0.f, 1.f})
{
	m_dir.Normalize();
}

Missile::~Missile()
{
}

void Missile::Update()
{
	Vector2 vPos = GetPos();
	// vPos.x += 200.f * DeltaTimef * cosf(m_dir);
	// vPos.y -= 200.f * DeltaTimef * sinf(m_dir);
	vPos.x += 200.f * DeltaTimef * m_dir.x;
	vPos.y -= 200.f * DeltaTimef * m_dir.y;

	SetPos(vPos);
}

void Missile::Render(HDC _memDC)
{
	Vector2 vPos = GetPos();
	Vector2 scale = GetScale();

	Ellipse(_memDC,
		(int)(vPos.x - scale.x / 2.f),
		(int)(vPos.y - scale.y / 2.f),
		(int)(vPos.x + scale.x / 2.f),
		(int)(vPos.y + scale.y / 2.f));
}
