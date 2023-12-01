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
	// ���� �����ӿ��� ����ó���� ������Ʈ�� ����
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
		// ������Ʈ�� Dead���·� ���� ��, ������ ������ ������Ʈ�� ��Ƶд�.
		// ���� �����ӿ� �ش� ������Ʈ�� ����
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
