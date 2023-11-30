#include "pch.h"
#include "Button.h"

Button::Button() :
	UI(false), m_pFunc(nullptr), m_param1(0), m_param2(0),
	m_pSceneFunc(nullptr), m_pSceneInst(nullptr)
{
}

Button::~Button()
{
}

//void Button::Update()
//{
//}
//
//void Button::FinalUpdate()
//{
//}
//
//void Button::Render(HDC _dc)
//{
//	UI::Render(_dc);
//}

void Button::MouseOn()
{
}

void Button::MouseLBtnClick()
{
	if (m_pFunc != nullptr) {
		m_pFunc(m_param1, m_param2);
	}

	if (m_pSceneFunc && m_pSceneInst) {
		((*m_pSceneInst).*m_pSceneFunc)();
	}
}

void Button::MouseLBtnUp()
{
}

void Button::MouseLBtnDown()
{
}

void Button::MouseRBtnClick()
{
}

void Button::MouseRBtnUp()
{
}

void Button::MouseRBtnDown()
{
}
