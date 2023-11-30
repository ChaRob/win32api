#include "pch.h"
#include "SceneMgr.h"
#include "CScene_Start.h"
#include "SceneTool.h"

SceneMgr::SceneMgr() :m_arrScene{}, m_pCurScene(nullptr) {

}

SceneMgr::~SceneMgr() {
	// 씬 전부 삭제
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; i++)
	{
		if(m_arrScene[i] != nullptr) delete m_arrScene[i];
	}
}

void SceneMgr::Init()
{
	// Scene 생성
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");
	
	m_arrScene[(UINT)SCENE_TYPE::TOOL] = new SceneTool;
	m_arrScene[(UINT)SCENE_TYPE::TOOL]->SetName(L"Tool Scene");

	// 현재 씬 저장
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];
	m_pCurScene->Enter();
}

void SceneMgr::Update()
{
	m_pCurScene->Update();
	m_pCurScene->FinalUpdate();
}

void SceneMgr::Render(HDC _memDC)
{
	m_pCurScene->Render(_memDC);
}

void SceneMgr::ChangeCurScene(SCENE_TYPE _scene)
{
	m_pCurScene->Exit();
	m_pCurScene = m_arrScene[(UINT)_scene];
	m_pCurScene->Enter();
}
