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
	UI* GetTargetedUI(UI* _pParentUI, bool LbTap, bool LbAway);	// �θ� UI������ ������ Ÿ���� �� UI�� ã�Ƽ� ��ȯ�Ѵ�.
	UI* GetForcusedUI(bool LbTap, bool LbAway);					// ��� �θ� UI���� ��Ŀ������ UI�� ã�´�.

public:
	void SetForcusUI(UI* _target);

};

