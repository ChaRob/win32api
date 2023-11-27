#include "pch.h"
#include "CScene.h"
#include "Tile.h"
#include "ResourceMgr.h"

CScene::CScene():
	m_tileX(0), m_tileY(0)
{
}

CScene::~CScene()
{
	// 모든 오브젝트 제거
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (int j = 0; j < m_arrObj[i].size(); j++) {
			delete m_arrObj[i][j];
		}
	}
}

void CScene::Update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (int j = 0; j < m_arrObj[i].size(); j++)
		{
			if (!m_arrObj[i][j]->IsDead())
			{
				m_arrObj[i][j]->Update();
			}
		}
	}
}

void CScene::Render(HDC _memDC)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		vector<CObject*>::iterator iter = m_arrObj[i].begin();

		for (; iter != m_arrObj[i].end();)
		{
			if (!(*iter)->IsDead())
			{
				(*iter)->Render(_memDC);
				iter++;
			}
			else {
				iter = m_arrObj[i].erase(iter);
			}
		}
	}
}

void CScene::FinalUpdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (int j = 0; j < m_arrObj[i].size(); j++)
		{
			m_arrObj[i][j]->FinalUpdate();
		}
	}
}

void CScene::DeleteGroup(GROUP_TYPE _group)
{
	SafeDeleteVector<CObject*>(m_arrObj[(UINT)_group]);
}

void CScene::DeleteGroupAll()
{
	for (int i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}

void CScene::CreateTile(UINT _xCount, UINT _yCount)
{
	CTexture* pTex = ResourceMgr::GetInstance()->LoadTexture(L"Tile", L"texture\\Tile.bmp");

	for (UINT i = 0; i < _xCount; i++)
	{
		for (UINT j = 0; j < _yCount; j++)
		{
			Tile* tile = new Tile();
			tile->SetPos(Vector2{ (float)(j * TILE_SIZE), (float)(i * TILE_SIZE) });
			tile->SetTexture(pTex);
			AddObject(tile, GROUP_TYPE::TILE);
		}
	}
	m_tileX = _xCount;
	m_tileY = _yCount;
}
