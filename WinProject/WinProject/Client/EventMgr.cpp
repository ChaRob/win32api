#include "pch.h"
#include "EventMgr.h"
#include "CScene.h"
#include "SceneMgr.h"
#include "UIMgr.h"
#include "AI.h"
#include "State.h"

EventMgr::EventMgr()
{

}

EventMgr::~EventMgr()
{

}

void EventMgr::Init()
{
}

void EventMgr::Update()
{
	// 이전 프레임에서 죽음처리된 오브젝트들 제거
	for (int i = 0; i < m_vecDeadObj.size(); i++)
	{
		delete m_vecDeadObj[i];
	}
	m_vecDeadObj.clear();

	for (int i = 0; i < m_vecEvent.size(); i++)
	{
		Excute(m_vecEvent[i]);
	}

	m_vecEvent.clear();
}

void EventMgr::Excute(const tEvent& _event)
{
	switch (_event.eEvent)
	{
	case EVENT_TYPE::CREATE_OBJECT:
		// lParam : Object Adress
		// wParam : Group Type
	{
		CObject* pNewObj = (CObject*)_event.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_event.wParam;

		SceneMgr::GetInstance()->GetCurScene()->AddObject(pNewObj, eType);
	}
		break;
	case EVENT_TYPE::DELETE_OBJECT:
		// lParam : Object Adress
		// 오브젝트를 Dead상태로 변경 후, 삭제할 예정인 오브젝트에 담아둔다.
		// 다음 프레임에 해당 오브젝트를 제거
	{
		CObject* pDeadObj = (CObject*)_event.lParam;
		if (!pDeadObj->IsDead()) {
			m_vecDeadObj.push_back(pDeadObj);
			pDeadObj->SetDead();
		}
	}
		break;
	case EVENT_TYPE::SCENE_CHANGE:
		// lParam : Next Scene Type
		SceneMgr::GetInstance()->ChangeCurScene((SCENE_TYPE)_event.lParam);
		UIMgr::GetInstance()->SetForcusUI(nullptr);
		break;
	case EVENT_TYPE::AISTATE_CHANGE:
		// IParam : AI
		// wParam : next state
		AI* ai = (AI*)_event.lParam;
		MON_STATE nextState = (MON_STATE)_event.wParam;

		ai->ChangeState(nextState);

		break;
	}
}
