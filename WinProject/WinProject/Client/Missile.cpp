#include "pch.h"
#include "Missile.h"
#include "CTimeMgr.h"
#include "Collider.h"
#include "Camera.h"

Missile::Missile() : m_dir(Vector2{0.f, 1.f})
{
	m_dir.Normalize();
	CreateCollider();
	GetCollider()->SetSize(Vector2{ 10.f,10.f });
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
	Vector2 renderPos = Camera::GetInstance()->GetRenderPos(vPos);

	Ellipse(_memDC,
		(int)(renderPos.x - scale.x / 2.f),
		(int)(renderPos.y - scale.y / 2.f),
		(int)(renderPos.x + scale.x / 2.f),
		(int)(renderPos.y + scale.y / 2.f));

	ComponentRender(_memDC);
}

void Missile::OnCollisionEnter(Collider* _pOther)
{
	CObject* pOtherObj = _pOther->GetOwnerObject();
	if (pOtherObj->GetName() == L"Monster") {
		DeleteObejct(this);
	}
}
