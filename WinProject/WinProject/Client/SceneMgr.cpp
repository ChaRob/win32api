#include "pch.h"
#include "SceneMgr.h"
#include "CScene_Start.h"

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

	// 현재 씬 저장
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];
	m_pCurScene->Enter();
}

void SceneMgr::Update()
{
	m_pCurScene->Update();

}

void SceneMgr::Render(HDC _memDC)
{
	m_pCurScene->Render(_memDC);
}
