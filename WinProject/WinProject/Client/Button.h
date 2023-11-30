#pragma once
#include "UI.h"
#include "CScene.h"
#include "CObject.h"

typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

typedef void(CScene::* SCENE_MEMFUNC)(void);
typedef void(CObject::* OBJECT_MEMFUNC)(void);

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

	SCENE_MEMFUNC m_pSceneFunc;
	CScene* m_pSceneInst;

public:
	void SetClickCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2) {
		m_pFunc = _pFunc;
		m_param1 = _param1;
		m_param2 = _param2;
	}

	void SetClickCallBack(SCENE_MEMFUNC _memFunc, CScene* _pScene) {
		m_pSceneFunc = _memFunc;
		m_pSceneInst = _pScene;
	}
};

