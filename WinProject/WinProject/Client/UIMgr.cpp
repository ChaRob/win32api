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
	// 1. 부모 UI 포함, 모든 자식들을 검사한다.
	// 2. 자식 UI가 우선적으로 이벤트가 발생되도록 한다.
	UI* pTargetUI = nullptr;

	bool LbTap = KEY_TAP(KEY::LMBTN);
	bool LbAway = KEY_AWAY(KEY::LMBTN);

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
