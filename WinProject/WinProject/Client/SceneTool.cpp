#include "pch.h"
#include "SceneTool.h"
#include "CKeyMgr.h"
#include "Tile.h"
#include "Camera.h"
#include "ResourceMgr.h"

SceneTool::SceneTool()
{
}

SceneTool::~SceneTool()
{
}

void SceneTool::Update()
{
	CScene::Update();
}

void SceneTool::Enter()
{
	// 타일 텍스쳐 불러오기
	CTexture* pTex = ResourceMgr::GetInstance()->LoadTexture(L"Tile", L"texture\\Tile.bmp");


	// 타일 생성
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			Tile* tile = new Tile();
			tile->SetPos(Vector2{ j * TILE_SIZE, i * TILE_SIZE });
			tile->SetTexture(pTex);
			AddObject(tile, GROUP_TYPE::TILE);
		}
	}

	Vector2 vResolution = CCore::GetInstance()->GetResolution();
	Camera::GetInstance()->SetLookAt(vResolution / 2);
}

void SceneTool::Exit()
{
}
