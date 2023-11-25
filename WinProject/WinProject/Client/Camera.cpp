#include "pch.h"
#include "Camera.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"

Camera::Camera() :
	m_LookAt{}, m_PrevLookAt{}, m_CurLookAt {},
	m_targetObj(nullptr), m_Diff{}, m_time(1.f),
	m_accTime(0.f), m_speed(0.f)
{
}

Camera::~Camera(){

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
	m_accTime += DeltaTime;

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
