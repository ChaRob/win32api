#include "pch.h"
#include "Collider.h"
#include "CCore.h"
#include "SelectGDI.h"

Collider::Collider() :
	m_pOwner(0), m_offsetPos{}, m_finalPos{}, m_size{}
{
}

Collider::~Collider()
{
}

void Collider::FinalUpdate()
{
	// ������Ʈ�� ������ ��ġ�� ���󰣴�
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
