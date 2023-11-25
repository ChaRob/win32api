#include "pch.h"
#include "CScene_Start.h"

#include "CTexture.h"
#include "PathManager.h"
#include "CObject.h"
#include "Player.h"
#include "Monster.h"

#include "CollisionMgr.h"
#include "CKeyMgr.h"
#include "SceneMgr.h"
#include "Camera.h"

CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::Update()
{
	CScene::Update();
	if (KEY_TAP(KEY::ENTER)) {
		ChangeScene(SCENE_TYPE::TOOL);
	}

	if (KEY_TAP(KEY::LMBTN)) {
		Vector2 mousePos = Camera::GetInstance()->GetRealPos(MOUSE_POS);
		Camera::GetInstance()->SetLookAt(mousePos);
	}
}

void CScene_Start::Enter()
{
	// Object 추가
	CObject* pObj = new Player;
	pObj->SetPos(Vector2{ 640.f, 384.f });
	pObj->SetScale(Vector2{ 100, 100 });
	AddObject(pObj, GROUP_TYPE::PLAYER);

	//// player 복사
	//CObject* newPObj = pObj->Clone();
	//newPObj->SetPos(Vector2{ 740.f, 384.f });
	//AddObject(newPObj, GROUP_TYPE::PLAYER);

	int monsterCnt = 5;
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
		mObj->SetName(L"Monster");
		AddObject(mObj, GROUP_TYPE::MONSTER);
	}

	// 충돌 지정
	// Player 그룹과 Monster 그룹 간의 충돌 체크
	CollisionMgr::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CollisionMgr::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER_MISSILE, GROUP_TYPE::MONSTER);

	//Camera::GetInstance()->SetLookAt(Vector2(CCore::GetInstance()->GetResolution()) / 2);

	// 카메라를 플레이어 오브젝트 중심을 따라가도록 설정
	// Camera::GetInstance()->SetTargetObj(pObj);
}

void CScene_Start::Exit()
{
	DeleteGroupAll();

	CollisionMgr::GetInstance()->DeleteGroup();
}
