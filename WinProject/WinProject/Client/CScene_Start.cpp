#include "pch.h"
#include "CScene_Start.h"

#include "CObject.h"
#include "Player.h"
#include "Monster.h"

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::Enter()
{
	// Object Ãß°¡
	CObject* pObj = new Player;
	pObj->SetPos(Vector2{ 640.f, 384.f });
	pObj->SetScale(Vector2{ 100, 100 });
	AddObject(pObj, GROUP_TYPE::DEFALUT);

	int monsterCnt = 20;
	float maxDistance = 25.f;
	float scale = 50.f;
	Vector2 vResolution = CCore::GetInstance()->GetResolution();
	float fTerm = (vResolution.x - (maxDistance + scale/2.f) * 2) / (float)(monsterCnt - 1);
	Monster* mObj = nullptr;

	for (int i = 0; i < monsterCnt; i++)
	{
		mObj = new Monster;
		mObj->SetMaxDistance(maxDistance);
		mObj->SetPos(Vector2{ maxDistance + scale / 2.f + fTerm * i, 100.f });
		mObj->SetScale(Vector2{ scale, scale });
		mObj->SetCenterPos(mObj->GetPos());
		AddObject(mObj, GROUP_TYPE::MONSTER);
	}
}

void CScene_Start::Exit()
{
}
