#include "pch.h"
#include "CObject.h"

CObject::CObject() :
	m_pos{}, m_size{}
{
}

CObject::~CObject()
{
}

void CObject::Update()
{
	
}

void CObject::Render(HDC _memDC)
{
	Rectangle(_memDC,
		(int)(m_pos.x - m_size.x / 2.f),
		(int)(m_pos.y - m_size.y / 2.f),
		(int)(m_pos.x + m_size.x / 2.f),
		(int)(m_pos.y + m_size.y / 2.f));
}
