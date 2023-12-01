#include "pch.h"
#include "CScene.h"
#include "Tile.h"
#include "ResourceMgr.h"
#include "Camera.h"
#include "UI.h"
#include "PathManager.h"

CScene::CScene():
	m_tileX(0), m_tileY(0), m_player(nullptr)
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
		// 타일 최적화 렌더링
		if (i == (UINT)GROUP_TYPE::TILE) {
			Render_Tile(_memDC);
			continue;
		}

		vector<CObject*>::iterator iter = m_arrObj[i].begin();

		for (; iter != m_arrObj[i].end();)
		{
			if (!(*iter)->IsDead())
			{
				Vector2 resoultion = CCore::GetInstance()->GetResolution();
				Vector2	pos = (*iter)->GetPos();
				Vector2 renPos = Camera::GetInstance()->GetRenderPos(pos);
				UI* pUI = dynamic_cast<UI*>(*iter);
				if (pUI != nullptr && !pUI->IsCamEffected()) {
					(*iter)->Render(_memDC);
				}
				else {
				if (-TILE_SIZE <= renPos.x && renPos.x <= resoultion.x + TILE_SIZE &&
					-TILE_SIZE <= renPos.y && renPos.y <= resoultion.y + TILE_SIZE)
				{
					(*iter)->Render(_memDC);
				}
				}
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
	DeleteGroup(GROUP_TYPE::TILE);
	CTexture* pTex = ResourceMgr::GetInstance()->LoadTexture(L"Tile", L"texture\\Tile.bmp");

	for (UINT i = 0; i < _yCount; i++)
	{
		for (UINT j = 0; j < _xCount; j++)
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

CObject* const CScene::DeleteObjectInGroup(GROUP_TYPE _type, CObject* _target)
{
	vector<CObject*>::iterator iter = m_arrObj[(UINT)_type].begin();
	for (; iter != m_arrObj[(UINT)_type].end(); iter++)
	{
		if (*iter == _target) {
			m_arrObj[(UINT)_type].erase(iter);
			break;
		}
	}
	return _target;
}

void CScene::LoadData(const wstring& _strRelativePath)
{
	FILE* file = nullptr;
	wstring strFilePath = PathManager::GetInstance()->GetContentPath() + _strRelativePath;

	// stream 개방
	_wfopen_s(&file, strFilePath.c_str(), L"rb"); // wb : binary Mode
	// 파일 불러오기 실패
	assert(file);

	// 데이터 불러오기
	UINT xCount;
	UINT yCount;

	fread(&xCount, sizeof(UINT), 1, file);
	fread(&yCount, sizeof(UINT), 1, file);

	CreateTile(xCount, yCount);

	const vector<CObject*> vecTile = GetGroupObject(GROUP_TYPE::TILE);
	for (size_t i = 0; i < vecTile.size(); i++)
	{
		((Tile*)vecTile[i])->LoadTileObject(file);
	}

	// stream 닫기
	fclose(file);
}

void CScene::Render_Tile(HDC _dc)
{
	vector<CObject*> vecTile = GetGroupObject(GROUP_TYPE::TILE);

	Vector2 cameraLook = Camera::GetInstance()->GetLookAt();
	Vector2 resolution = CCore::GetInstance()->GetResolution();

	Vector2 leftTop = cameraLook - resolution / 2.f;

	int tileSize = TILE_SIZE;

	int col = (int)leftTop.x / tileSize;
	int row = (int)leftTop.y / tileSize;

	int clientWidth = (int)resolution.x / tileSize;
	int clientHeight = (int)resolution.y / tileSize;

	for (int i = row; i <= row + clientHeight; i++)
	{
		for (int j = col; j <= col + clientWidth; j++)
		{
			// 타일 인덱스 범위를 벗어나면 다음 타일로
			if (i < 0 || m_tileX <= i ||
				j < 0 || m_tileY <= j)
			{
				continue;
			}

			int idx = m_tileX * i + j;
			if (idx >= 0) {
				vecTile[idx]->Render(_dc);
			}
		}
	}
}
