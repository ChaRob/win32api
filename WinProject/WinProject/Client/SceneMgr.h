#pragma once

// ���漱��
class CScene;

class SceneMgr
{
	SINGLE(SceneMgr);
	friend class EventMgr;
private:
	CScene* m_arrScene[(UINT)SCENE_TYPE::END];	// ��� �� ���
	CScene* m_pCurScene;						// ���� ��

public:
	void Init();
	void Update();
	void Render(HDC _memDc);
	CScene* GetCurScene() { return m_pCurScene; }
	void ChangeCurScene(SCENE_TYPE _scene);
};

