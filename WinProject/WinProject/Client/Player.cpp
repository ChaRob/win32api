#include "pch.h"
#include "Player.h"

#include "CTexture.h"
#include "PathManager.h"
#include "ResourceMgr.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "SceneMgr.h"
#include "CScene.h"
#include "Collider.h"

#include "Missile.h"
#include "Animator.h"
#include "Animation.h"
#include "Camera.h"

Player::Player()
{
	CreateCollider();
	GetCollider()->SetOffsetPos(Vector2{ 0.f, 0.f });
	GetCollider()->SetSize(Vector2{ 50.f, 50.f });

	// texture 불러오기
	// m_pTex = ResourceMgr::GetInstance()->LoadTexture(L"PlayerTex", L"texture\\test.bmp");
	/*CTexture* m_pTex = ResourceMgr::GetInstance()->LoadTexture(L"PlayerTex", L"texture\\zelda.bmp");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"Walk_down", m_pTex, Vector2{0.f, 260.f}, Vector2{60.f, 65.f}, Vector2{60.f,0.f}, 0.1f, 10);

	GetAnimator()->Play(L"Walk_down", true);

	Animation* pAnim = GetAnimator()->FindAnimation(L"Walk_down");
	for (int i = 0; i < pAnim->GetMaxFrame(); i++)
	{
		pAnim->GetFrame(i).offset = Vector2{ 0.f, -20.f };
	}*/
}

Player::~Player()
{
}

void Player::Update()
{
	Vector2 vPos = GetPos();

	if (KEY_HOLD(KEY::W)) {
		vPos.y -= 200.f * DeltaTimef;
	}
	if (KEY_HOLD(KEY::S)) {
		vPos.y += 200.f * DeltaTimef;
	}
	if (KEY_HOLD(KEY::A)) {
		vPos.x -= 200.f * DeltaTimef;
	}
	if (KEY_HOLD(KEY::D)) {
		vPos.x += 200.f * DeltaTimef;
	}
	SetPos(vPos);

	if (KEY_TAP(KEY::SPACE)) {
		CreateMissile();
	}
	
	if (GetAnimator() != nullptr) {
		GetAnimator()->Update();
	}
}

void Player::Render(HDC _memDC)
{
	// 비트맵에 들어가는 값은 항상 양수(unsigned)이지만, 
	// 실제 좌표값은 음수가 가능하기 때문에
	// int로 형변환을 해준다.

	CTexture* m_pTex = ResourceMgr::GetInstance()->LoadTexture(L"PlayerTex", L"texture\\zelda_alpha.bmp");
	
	Vector2 renPos = Camera::GetInstance()->GetRenderPos(GetPos());

	float width = (float)m_pTex->GetBitmapWidth();
	float height = (float)m_pTex->GetBitmapHeight();

	BLENDFUNCTION bf = {};
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.BlendFlags = 0;
	bf.BlendOp = AC_SRC_OVER;
	bf.SourceConstantAlpha = 255;

	AlphaBlend(_memDC,
		(int)(renPos.x - width / 2.f),
		(int)(renPos.y - height / 2.f),
		(int)(width),
		(int)(height),
		m_pTex->GetDC(),
		0, 0, width, height,
		bf);
	
	/*int width = (int)m_pTex->GetBitmapWidth();
	int height = (int)m_pTex->GetBitmapHeight();

	Vector2 pPos = GetPos();

	BitBlt(_memDC,
		pPos.x - (float)(width / 2.f),
		pPos.y - (float)(height / 2.f),
		width, height, m_pTex->GetDC(), 0, 0, SRCCOPY);

	TransparentBlt(_memDC,
		(int)(pPos.x - (float)(width / 2.f)),
		(int)(pPos.y - (float)(height / 2.f)),
		width, height, m_pTex->GetDC(),
		0, 0, width, height,
		RGB(255, 0, 255));*/

	// 애니메이션에 의해 렌더링해주기
	ComponentRender(_memDC);
}

void Player::CreateMissile()
{
	Vector2 missilePos = GetPos();
	missilePos.y -= GetScale().y / 2.f;

	Missile* pMissile = new Missile;
	pMissile->SetPos(missilePos);
	pMissile->SetScale(Vector2{ 25.f, 25.f });
	pMissile->SetDir(Vector2{0.f, 1.f});
	pMissile->SetName(L"PlayerMissle");

	//CScene* pCurScene = SceneMgr::GetInstance()->GetCurScene();
	//pCurScene->AddObject(pMissile, GROUP_TYPE::MISSILE);

	CreateObject(pMissile, GROUP_TYPE::PLAYER_MISSILE);
}
