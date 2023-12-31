#include "UI.h"
#include "Camera.h"
#include "CKeyMgr.h"
#include "SelectGDI.h"

UI::UI(bool _isCamAffected):
	m_parentUI(nullptr), m_childUI{},
	m_finalPos{}, m_camAffected(_isCamAffected),
	m_mouseOn(false), m_LBtnDown(false)
{
}

// 복사 생성자. 더 상위의 부모 클래스도 복사 생성자를 호출하도록 해야함.
// 그렇지 않으면 기본 생성자를 호출함.
UI::UI(const UI& _origin): CObject(_origin),
	m_parentUI(nullptr), m_camAffected(_origin.m_camAffected),
	m_mouseOn(false), m_LBtnDown(false)
{
	m_finalPos = _origin.m_finalPos;
	for (int i = 0; i < _origin.m_childUI.size(); i++)
	{
		AddChildUI(_origin.m_childUI[i]->Clone());
	}
}

UI::~UI()
{
	SafeDeleteVector(m_childUI);
}

void UI::Update()
{
	UpdateChild();
}

void UI::FinalUpdate()
{
	CObject::FinalUpdate();

	// UI의 최종 위치를 구한다.
	m_finalPos = GetPos();

	if (GetParent() != nullptr) {
		Vector2 finalPos = GetParent()->GetFinalPos();
		m_finalPos += finalPos;
	}
	MouseOnCheck();

	FinalUpdateChild();
}

void UI::Render(HDC _dc)
{
	Vector2 pos = GetFinalPos();
	Vector2 scale = GetScale();

	if (m_camAffected) {
		pos = Camera::GetInstance()->GetRenderPos(pos);
	}
	if (m_LBtnDown) {
		SelectGDI select = SelectGDI(_dc, PEN_TYPE::GREEN);

		Rectangle(_dc,
			(int)pos.x,
			(int)pos.y,
			(int)(pos.x + scale.x),
			(int)(pos.y + scale.y));
	}
	else {

		Rectangle(_dc,
			(int)pos.x,
			(int)pos.y,
			(int)(pos.x + scale.x),
			(int)(pos.y + scale.y));
	}

	RenderChild(_dc);
}

void UI::MouseOn()
{
}

void UI::MouseLBtnClick()
{
}

void UI::MouseLBtnUp()
{
}

void UI::MouseLBtnDown()
{
}

void UI::MouseRBtnClick()
{
}

void UI::MouseRBtnUp()
{
}

void UI::MouseRBtnDown()
{
}

void UI::UpdateChild()
{
	for (int i = 0; i < m_childUI.size(); i++)
	{
		m_childUI[i]->Update();
	}
}

void UI::FinalUpdateChild()
{
	for (int i = 0; i < m_childUI.size(); i++)
	{
		m_childUI[i]->FinalUpdate();
	}
}

void UI::RenderChild(HDC _dc)
{
	for (int i = 0; i < m_childUI.size(); i++)
	{
		m_childUI[i]->Render(_dc);
	}
}

void UI::MouseOnCheck()
{
	Vector2 mousePos = MOUSE_POS;
	Vector2	scale = GetScale();
	if (m_camAffected) {
		mousePos = Camera::GetInstance()->GetRealPos(mousePos);
	}

	if (m_finalPos.x <= mousePos.x && mousePos.x <= m_finalPos.x + scale.x &&
		m_finalPos.y <= mousePos.y && mousePos.y <= m_finalPos.y + scale.y
		) {
		m_mouseOn = true;
	}
	else {
		m_mouseOn = false;
	}
}
