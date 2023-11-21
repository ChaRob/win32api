#pragma once

// 전방선언
class CScene;

class SceneMgr
{
	SINGLE(SceneMgr);
private:
	CScene* m_arrScene[(UINT)SCENE_TYPE::END];	// 모든 씬 목록
	CScene* m_pCurScene;						// 현재 씬

public:
	void Init();
	void Update();
	void Render(HDC _memDc);
	CScene* GetCurScene() { return m_pCurScene; }
};

