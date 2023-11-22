#include "pch.h"
#include "SelectGDI.h"
#include "CCore.h"

SelectGDI::SelectGDI(HDC _dc, PEN_TYPE _pen):
	m_hDC(_dc), m_hDefalutBrush(nullptr), m_hDefalutPen(nullptr)
{
	HPEN hNewPen = CCore::GetInstance()->GetPen(_pen);
	m_hDefalutPen = (HPEN)SelectObject(m_hDC, hNewPen);
}

SelectGDI::SelectGDI(HDC _dc, BRUSH_TYPE _brush):
	m_hDC(_dc), m_hDefalutBrush(nullptr), m_hDefalutPen(nullptr)
{
	HBRUSH hNewBrush = CCore::GetInstance()->GetBrush(_brush);
	m_hDefalutBrush = (HBRUSH)SelectObject(_dc, hNewBrush);
}

SelectGDI::~SelectGDI()
{
	SelectObject(m_hDC, m_hDefalutBrush);
	SelectObject(m_hDC, m_hDefalutPen);
}
