#pragma once
#include "CObject.h"
#include "UIMgr.h"

class UI : public CObject
{
	friend class UIMgr;
public:
	UI(bool _isCamAffectd);
	virtual ~UI();

private:
	vector<UI*> m_childUI;
	UI* m_parentUI;	// �θ� UI, nullptr�̶�� �ֻ��� �θ� ������Ʈ

	Vector2 m_finalPos;
	bool m_camAffected; // ī�޶� ������ �޴��� Ȯ���ϴ� ����
	bool m_mouseOn;		// ���콺�� �ش� UI�� �ö�� �ִ��� Ȯ���ϴ� ����
	bool m_LBtnDown;	// ���콺 ���� ��ư�� �ش� UI�� ���Ⱦ����� Ȯ���ϴ� ����

public:
	virtual void Update();
	virtual void FinalUpdate();
	virtual void Render(HDC _dc);
	virtual CObject* Clone() { return new UI(*this); }

	virtual void MouseOn();

	virtual void MouseLBtnClick();
	virtual void MouseLBtnUp();
	virtual void MouseLBtnDown();

	virtual void MouseRBtnClick();
	virtual void MouseRBtnUp();
	virtual void MouseRBtnDown();

private:
	void UpdateChild();
	void FinalUpdateChild();
	void RenderChild(HDC _dc);
	
	void MouseOnCheck();

public:
	UI* GetParent() { return m_parentUI; }
	void AddChildUI(UI* _child) {
		m_childUI.push_back(_child);
		_child->m_parentUI = this;
	}
	Vector2 GetFinalPos() { return m_finalPos; }
	bool IsMouseOn() { return m_mouseOn; }

};

