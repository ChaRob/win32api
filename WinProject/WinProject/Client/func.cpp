#include "pch.h"
#include "func.h"
#include "EventMgr.h"

void CreateObject(CObject* _pObj, GROUP_TYPE _group)
{
	tEvent newEvent = {};
	newEvent.eEvent = EVENT_TYPE::CREATE_OBJECT;
	newEvent.lParam = (DWORD_PTR)_pObj;
	newEvent.wParam = (DWORD_PTR)_group;

	EventMgr::GetInstance()->AddEvent(newEvent);
}

void DeleteObejct(CObject* _pObj)
{
	tEvent newEvent = {};
	newEvent.eEvent = EVENT_TYPE::DELETE_OBJECT;
	newEvent.lParam = (DWORD_PTR)_pObj;

	EventMgr::GetInstance()->AddEvent(newEvent);
}

void ChangeScene(SCENE_TYPE _scene)
{
	tEvent newEvent = {};
	newEvent.eEvent = EVENT_TYPE::SCENE_CHANGE;
	newEvent.lParam = (DWORD_PTR)_scene;

	EventMgr::GetInstance()->AddEvent(newEvent);
}

void ChangeAIState(AI* _ai, MON_STATE _nextState)
{
	tEvent newEvent = {};
	newEvent.eEvent = EVENT_TYPE::AISTATE_CHANGE;
	newEvent.lParam = (DWORD_PTR)_ai;
	newEvent.wParam = (DWORD_PTR)_nextState;

	EventMgr::GetInstance()->AddEvent(newEvent);
}
