#pragma once
#include "UI.h"
class Panel :
    public UI
{
public:
    Panel();
	virtual ~Panel();

private:
	Vector2 m_DragStart;

public:
	/*virtual void Update();
	virtual void FinalUpdate();
	virtual void Render(HDC _dc);*/
	Panel* Clone() { return new Panel(*this); }

	virtual void MouseOn();

	virtual void MouseLBtnClick();
	virtual void MouseLBtnUp();
	virtual void MouseLBtnDown();

	virtual void MouseRBtnClick();
	virtual void MouseRBtnUp();
	virtual void MouseRBtnDown();
};

