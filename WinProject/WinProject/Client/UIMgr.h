#pragma once
class UI;

class UIMgr
{
	SINGLE(UIMgr);


public:
	void Init();
	void Update();

private:
	UI* GetTargetedUI(UI* _pParentUI); // 부모 UI내에서 실제로 타겟팅 된 UI를 찾아서 반환한다.

};

