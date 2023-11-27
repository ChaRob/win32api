#include "pch.h"
#include "Panel.h"
#include "CKeyMgr.h"

Panel::Panel():
	UI(false), m_DragStart{}
{
}

Panel::~Panel()
{
}

//void Panel::Update()
//{
//}
//
//void Panel::FinalUpdate()
//{
//}
//
//void Panel::Render(HDC _dc)
//{
//	UI::Render(_dc);
//}

void Panel::MouseOn()
{
	if (IsLBtnDown()) {
		SetPos(GetPos() + MOUSE_POS - m_DragStart);
		m_DragStart = MOUSE_POS;
	}
}

void Panel::MouseLBtnClick()
{
}

void Panel::MouseLBtnUp()
{
}

void Panel::MouseLBtnDown()
{
	m_DragStart = MOUSE_POS;
}

void Panel::MouseRBtnClick()
{
}

void Panel::MouseRBtnUp()
{
}

void Panel::MouseRBtnDown()
{
}
