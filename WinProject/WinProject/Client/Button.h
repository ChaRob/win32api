#pragma once
#include "UI.h"
class Button :
    public UI
{
public:
    Button();
    virtual ~Button();

private:


public:
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
};

