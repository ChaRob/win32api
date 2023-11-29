#pragma once
#include "UI.h"

typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

class Button :
    public UI
{
public:
    Button();
    virtual ~Button();

	/*virtual void Update();
	virtual void FinalUpdate();
	virtual void Render(HDC _dc);*/
	Button* Clone() { return new Button(*this); }

	virtual void MouseOn();

	virtual void MouseLBtnClick();
	virtual void MouseLBtnUp();
	virtual void MouseLBtnDown();

	virtual void MouseRBtnClick();
	virtual void MouseRBtnUp();
	virtual void MouseRBtnDown();

private:
	BTN_FUNC m_pFunc;
	DWORD_PTR m_param1;
	DWORD_PTR m_param2;

public:
	void SetClickCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2) {
		m_pFunc = _pFunc;
		m_param1 = _param1;
		m_param2 = _param2;
	}
};

