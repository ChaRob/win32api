#include "pch.h"
#include "UIMgr.h"

#include "CScene.h"
#include "UI.h"
#include "SceneMgr.h"
#include "CKeyMgr.h"
#include <queue>
using std::queue;

UIMgr::UIMgr():
	m_pForcused(nullptr)
{

}

UIMgr::~UIMgr() {

}

void UIMgr::Init()
{

}

/*
	1. 현재 씬에서 Forcusing된 UI를 가져온다.
	2. 그 UI에서 타겟팅한 UI가 누구인지 찾는다.
	3. 해당 UI의 이벤트 처리를 진행한다.
*/
void UIMgr::Update()
{
	bool LbTap = KEY_TAP(KEY::LMBTN);
	bool LbAway = KEY_AWAY(KEY::LMBTN);

	m_pForcused = GetForcusedUI(LbTap, LbAway);

	if (m_pForcused == nullptr) return;

	// 현재 포커스(가장 상위 UI)된 오브젝트만의 이벤트를 받아온다.
	UI* targetedUI = GetTargetedUI(m_pForcused, LbTap, LbAway);

	if (targetedUI != nullptr) {
		targetedUI->MouseOn();

		if (LbTap) {
			targetedUI->m_LBtnDown = true;
			targetedUI->MouseLBtnDown();
		}
		else if (LbAway) {
			targetedUI->MouseLBtnUp();
			if (targetedUI->m_LBtnDown) {
				targetedUI->MouseLBtnClick();
			}

			targetedUI->m_LBtnDown = false;
		}
	}
}

UI* UIMgr::GetTargetedUI(UI* _pParentUI, bool LbTap, bool LbAway)
{
	// 1. 부모 UI 포함, 모든 자식들을 검사한다.
	// 2. 자식 UI가 우선적으로 이벤트가 발생되도록 한다.
	UI* pTargetUI = nullptr;

	// 자주 쓰는 변수들을 정적변수로 지정
	static vector<UI*> noneTarget;
	static queue<UI*> que;

	noneTarget.clear();
	while (!que.empty()) que.pop();

	que.push(_pParentUI);
	while (!que.empty()) {
		UI* nowUI = que.front();
		que.pop();

		for (int i = 0; i < nowUI->m_childUI.size(); i++)
		{
			que.push(nowUI->m_childUI[i]);
		}

		if (nowUI->IsMouseOn()) {
			if (pTargetUI != nullptr) noneTarget.push_back(pTargetUI);
			pTargetUI = nowUI;
		}
		else {
			noneTarget.push_back(nowUI);
		}
	}

	if (LbAway) {
		for (int i = 0; i < noneTarget.size(); i++)
		{
			noneTarget[i]->m_LBtnDown = false;
		}
	}

	return pTargetUI;
}

UI* UIMgr::GetForcusedUI(bool LbTap, bool LbAway)
{
	CScene* pCurScene = SceneMgr::GetInstance()->GetCurScene();
	const vector<CObject*>& vecUI = pCurScene->GetGroupObject(GROUP_TYPE::UI);

	UI* pForcusedUI = m_pForcused;

	if (!LbTap) {
		return pForcusedUI;
	}

	for (int i = (int)vecUI.size() - 1; i >= 0; i--)
	{
		if (((UI*)vecUI[i])->IsMouseOn()) {
			CObject* curTarget = pCurScene->DeleteObjectInGroup(GROUP_TYPE::UI, vecUI[i]);
			pCurScene->AddObject(curTarget, GROUP_TYPE::UI);
			pForcusedUI = (UI*)curTarget;
			break;
		}
	}

	return pForcusedUI;
}

void UIMgr::SetForcusUI(UI* _target)
{
	if (m_pForcused == _target || _target == nullptr) {
		m_pForcused = _target;
		return;
	}

	m_pForcused = _target;

	CScene* pCurScene = SceneMgr::GetInstance()->GetCurScene();
	const vector<CObject*>& vecUI = pCurScene->GetGroupObject(GROUP_TYPE::UI);

	for (int i = (int)vecUI.size() - 1; i >= 0; i--)
	{
		if (((UI*)vecUI[i]) == _target) {
			CObject* curTarget = pCurScene->DeleteObjectInGroup(GROUP_TYPE::UI, vecUI[i]);
			pCurScene->AddObject(curTarget, GROUP_TYPE::UI);
			break;
		}
	}
}
