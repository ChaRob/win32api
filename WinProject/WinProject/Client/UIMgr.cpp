#include "pch.h"
#include "UIMgr.h"

#include "CScene.h"
#include "UI.h"
#include "SceneMgr.h"
#include "CKeyMgr.h"
#include <queue>
using std::queue;

UIMgr::UIMgr()
{

}

UIMgr::~UIMgr() {

}

void UIMgr::Init()
{

}

void UIMgr::Update()
{
	CScene* pCurScene = SceneMgr::GetInstance()->GetCurScene();
	const vector<CObject*>& vecUI = pCurScene->GetGroupObject(GROUP_TYPE::UI);

	bool LbTap = KEY_TAP(KEY::LMBTN);
	bool LbAway = KEY_AWAY(KEY::LMBTN);

	for (int i = 0; i < vecUI.size(); i++)
	{
		UI* pUI = dynamic_cast<UI*>(vecUI[i]);
		pUI = GetTargetedUI(pUI);

		if (pUI != nullptr) {
			pUI->MouseOn();

			if (LbTap) {
				pUI->m_LBtnDown = true;
				pUI->MouseLBtnDown();
			}
			else if (LbAway) {
				pUI->MouseLBtnUp();
				if (pUI->m_LBtnDown) {
					pUI->MouseLBtnClick();
				}

				pUI->m_LBtnDown = false;
			}
		}
	}
}

UI* UIMgr::GetTargetedUI(UI* _pParentUI)
{
	// 1. �θ� UI ����, ��� �ڽĵ��� �˻��Ѵ�.
	// 2. �ڽ� UI�� �켱������ �̺�Ʈ�� �߻��ǵ��� �Ѵ�.
	UI* pTargetUI = nullptr;

	bool LbTap = KEY_TAP(KEY::LMBTN);
	bool LbAway = KEY_AWAY(KEY::LMBTN);

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
