#pragma once
class UI;

class UIMgr
{
	SINGLE(UIMgr);


public:
	void Init();
	void Update();

private:
	UI* GetTargetedUI(UI* _pParentUI); // �θ� UI������ ������ Ÿ���� �� UI�� ã�Ƽ� ��ȯ�Ѵ�.

};

