#include "pch.h"
#include "Player.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "SceneMgr.h"
#include "CScene.h"

#include "Missile.h"

void Player::Update()
{
	Vector2 vPos = GetPos();

	if (KEY_HOLD(KEY::W)) {
		vPos.y -= 200.f * DeltaTime;
	}
	if (KEY_HOLD(KEY::S)) {
		vPos.y += 200.f * DeltaTime;
	}
	if (KEY_HOLD(KEY::A)) {
		vPos.x -= 200.f * DeltaTime;
	}
	if (KEY_HOLD(KEY::D)) {
		vPos.x += 200.f * DeltaTime;
	}
	SetPos(vPos);

	if (KEY_TAP(KEY::SPACE)) {
		CreateMissile();
	}
}

//void Player::Render(HDC _memDC)
//{
//}

void Player::CreateMissile()
{
	Vector2 missilePos = GetPos();
	missilePos.y -= GetScale().y / 2.f;

	Missile* pMissile = new Missile;
	pMissile->SetPos(missilePos);
	pMissile->SetScale(Vector2{ 25.f, 25.f });
	pMissile->SetDir(Vector2{0.f, 1.f});

	CScene* pCurScene = SceneMgr::GetInstance()->GetCurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::MISSILE);
}
