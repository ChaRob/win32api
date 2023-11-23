#include "pch.h"
#include "Collider.h"
#include "CCore.h"
#include "SelectGDI.h"

UINT Collider::s_nextID = 0;

Collider::Collider() :
	m_pOwner(0), m_offsetPos{}, m_finalPos{}, m_size{},
	m_ID(s_nextID++)
{
}

Collider::Collider(const Collider& _origin) :
	m_pOwner(nullptr), m_offsetPos(_origin.m_offsetPos),
	m_finalPos{}, m_size(_origin.m_size),
	m_ID(s_nextID++)
{
}

Collider::~Collider()
{
}

void Collider::FinalUpdate()
{
	// 오브젝트의 마지막 위치를 따라간다
	m_finalPos = m_pOwner->GetPos() + m_offsetPos;
}

void Collider::Render(HDC _memDC)
{
	SelectGDI p(_memDC, PEN_TYPE::GREEN);
	SelectGDI b(_memDC, BRUSH_TYPE::HOLLOW);

	Rectangle(_memDC,
		(int)(m_finalPos.x - m_size.x / 2.f),
		(int)(m_finalPos.y - m_size.y / 2.f),
		(int)(m_finalPos.x + m_size.x / 2.f),
		(int)(m_finalPos.y + m_size.y / 2.f));
}

void Collider::OnCollision(Collider* _pOther)
{
	m_pOwner->OnCollision(_pOther);
}

void Collider::OnCollisionEnter(Collider* _pOther)
{
	m_pOwner->OnCollisionEnter(_pOther);
}

void Collider::OnCollisionExit(Collider* _pOther)
{
	m_pOwner->OnCollisionExit(_pOther);
}
