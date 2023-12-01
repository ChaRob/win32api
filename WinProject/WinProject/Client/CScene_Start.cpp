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
#include "AI.h"
#include "IdleState.h"
#include "TraceState.h"

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
	// Object �߰�
	CObject* pObj = new Player;
	pObj->SetPos(Vector2{ 640.f, 384.f });
	pObj->SetScale(Vector2{ 100, 100 });
	AddObject(pObj, GROUP_TYPE::PLAYER);

	RegisterPlayer(pObj);

	//// player ����
	//CObject* newPObj = pObj->Clone();
	//newPObj->SetPos(Vector2{ 740.f, 384.f });
	//AddObject(newPObj, GROUP_TYPE::PLAYER);

	/*
	int monsterCnt = 1;
	float maxDistance = 25.f;
	float scale = 50.f;
	Vector2 vResolution = CCore::GetInstance()->GetResolution();
	float fTerm = (vResolution.x - (maxDistance + scale/2.f) * 2) / (float)(monsterCnt - 1);
	Monster* mObj = nullptr;

	AI* pAI = new AI;
	pAI->AddState(new IdleState);
	pAI->AddState(new TraceState);

	for (int i = 0; i < monsterCnt; i++)
	{
		mObj = new Monster;
		mObj->SetPos(Vector2{ maxDistance + scale / 2.f + fTerm * i, 100.f });
		mObj->SetScale(Vector2{ scale, scale });
		mObj->SetName(L"Monster");
		mObj->SetAI(pAI);
		//mObj->SetMaxDistance(maxDistance);
		//mObj->SetCenterPos(mObj->GetPos());
		AddObject(mObj, GROUP_TYPE::MONSTER);
	}
	*/

	Vector2 vResolution = CCore::GetInstance()->GetResolution();
	Monster* pMon = MonFactory::CreateMonster(MON_TYPE::NORMAL, vResolution / 2.f - Vector2(0.f, 300.f));
	CreateObject(pMon, GROUP_TYPE::MONSTER);

	// �浹 ����
	// Player �׷�� Monster �׷� ���� �浹 üũ
	CollisionMgr::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CollisionMgr::GetInstance()->CheckGroup(GROUP_TYPE::PLAYER_MISSILE, GROUP_TYPE::MONSTER);

	// Camera::GetInstance()->SetLookAt(Vector2(CCore::GetInstance()->GetResolution()) / 2);

	// ī�޶� �÷��̾� ������Ʈ �߽��� ���󰡵��� ����
	Camera::GetInstance()->SetTargetObj(pObj);

	// ī�޶� ȿ�� �׽�Ʈ
	// Camera::GetInstance()->FadeIn(5.f);
	// Camera::GetInstance()->FadeOut(5.f);
}

void CScene_Start::Exit()
{
	DeleteGroupAll();

	CollisionMgr::GetInstance()->DeleteGroup();
}
