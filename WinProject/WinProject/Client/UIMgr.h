#pragma once
class UI;

class UIMgr
{
	SINGLE(UIMgr);

private:
	UI* m_pForcused;

public:
	void Init();
	void Update();

private:
	UI* GetTargetedUI(UI* _pParentUI, bool LbTap, bool LbAway);	// 부모 UI내에서 실제로 타겟팅 된 UI를 찾아서 반환한다.
	UI* GetForcusedUI(bool LbTap, bool LbAway);					// 모든 부모 UI에서 포커싱중인 UI를 찾는다.

public:
	void SetForcusUI(UI* _target);

};

