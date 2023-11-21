#include "pch.h"
#include "SceneMgr.h"
#include "CScene_Start.h"

SceneMgr::SceneMgr() :m_arrScene{}, m_pCurScene(nullptr) {

}

SceneMgr::~SceneMgr() {
	// �� ���� ����
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; i++)
	{
		if(m_arrScene[i] != nullptr) delete m_arrScene[i];
	}
}

void SceneMgr::Init()
{
	// Scene ����
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");

	// ���� �� ����
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
