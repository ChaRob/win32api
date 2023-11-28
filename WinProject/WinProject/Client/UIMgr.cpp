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
	1. ���� ������ Forcusing�� UI�� �����´�.
	2. �� UI���� Ÿ������ UI�� �������� ã�´�.
	3. �ش� UI�� �̺�Ʈ ó���� �����Ѵ�.
*/
void UIMgr::Update()
{
	bool LbTap = KEY_TAP(KEY::LMBTN);
	bool LbAway = KEY_AWAY(KEY::LMBTN);

	m_pForcused = GetForcusedUI(LbTap, LbAway);

	if (m_pForcused == nullptr) return;

	// ���� ��Ŀ��(���� ���� UI)�� ������Ʈ���� �̺�Ʈ�� �޾ƿ´�.
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
	// 1. �θ� UI ����, ��� �ڽĵ��� �˻��Ѵ�.
	// 2. �ڽ� UI�� �켱������ �̺�Ʈ�� �߻��ǵ��� �Ѵ�.
	UI* pTargetUI = nullptr;

	// ���� ���� �������� ���������� ����
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
