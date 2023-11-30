#include "pch.h"
#include "Camera.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "ResourceMgr.h"
#include "CTexture.h"

Camera::Camera() :
	m_LookAt{}, m_PrevLookAt{}, m_CurLookAt {},
	m_targetObj(nullptr), m_Diff{}, m_time(1.f),
	m_accTime(0.f), m_speed(0.f), m_pVeilTex(nullptr),
	m_vecCamEffect{}
{
}

Camera::~Camera(){

}

void Camera::Init()
{
	Vector2 resolution = CCore::GetInstance()->GetResolution();
	// 검은색 장막을 만들기 위한 텍스쳐 생성
	// 이때, 이미 초기값으로 0이 들어가 있기에, 검은색으로 이미 초기화 된 상태가 된다.
	m_pVeilTex = ResourceMgr::GetInstance()->CreateTexture(L"CameraVeil", (UINT)resolution.x, (UINT)resolution.y);
}

void Camera::Update()
{
	if (m_targetObj != nullptr) {
		if (m_targetObj->IsDead()) {
			m_targetObj = nullptr;
		}
		else {
			m_LookAt = m_targetObj->GetPos();
		}
	}

	if (KEY_HOLD(KEY::UP)) {
		m_LookAt.y -= 500.f * DeltaTimef;
	}
	if (KEY_HOLD(KEY::DOWN)) {
		m_LookAt.y += 500.f * DeltaTimef;
	}
	if (KEY_HOLD(KEY::LEFT)) {
		m_LookAt.x -= 500.f * DeltaTimef;
	}
	if (KEY_HOLD(KEY::RIGHT)) {
		m_LookAt.x += 500.f * DeltaTimef;
	}

	// 매 업데이트마다 화면 중앙좌표와 카메라 Lookat 좌표간의 차이값 계산
	CalDiff();
}

void Camera::CalDiff()
{
	// 이전 LookAt과 현재 LookAt의 차이값을 보정해서 부드러운 움직임 구현
	m_accTime += DeltaTimef;

	if (m_accTime > m_time) {
		m_CurLookAt = m_LookAt;
	}
	else {
		Vector2 dir = (m_LookAt - m_PrevLookAt).Normalize();
		m_CurLookAt = m_PrevLookAt + dir * m_speed * DeltaTimef;
	}

	Vector2 resolutionCenter = Vector2(CCore::GetInstance()->GetResolution()) / 2;
	m_Diff = m_CurLookAt - resolutionCenter;

	m_PrevLookAt = m_CurLookAt;
}

void Camera::Render(HDC _dc)
{
	if (m_vecCamEffect.empty())
		return;

	float ratio = 0.f;
	camEffect& effect = m_vecCamEffect.front();
	effect.m_accDuration += DeltaTimef;

	if (effect.m_effect == CAM_EFFECT::FADE_IN) {
		ratio = effect.m_accDuration / effect.m_duration;
	}
	else {
		ratio = (1.f - effect.m_accDuration / effect.m_duration);
	}

	if		(ratio > 1.f) ratio = 1.f;
	else if (ratio < 0.f) ratio = 0.f;

	int alpha = (int)(255.f * ratio);

	float width = (float)m_pVeilTex->GetBitmapWidth();
	float height = (float)m_pVeilTex->GetBitmapHeight();

	BLENDFUNCTION bf = {};
	bf.AlphaFormat = 0;
	bf.BlendFlags = 0;
	bf.BlendOp = AC_SRC_OVER;
	bf.SourceConstantAlpha = alpha;

	AlphaBlend(_dc,
		0, 0, (int)(width), (int)(height),
		m_pVeilTex->GetDC(),
		0, 0, (int)(width), (int)(height),
		bf);

	if (effect.m_accDuration > effect.m_duration) {
		m_vecCamEffect.pop();
	}
}
