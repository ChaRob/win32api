#pragma once
#include "CObject.h"

class Camera
{
	SINGLE(Camera);
private:
	Vector2 m_LookAt;		// 현재 카메라가 보고 있는 위치 => 실제 좌표
	Vector2 m_PrevLookAt;	// 카메라가 보는 이전 프레임 위치
	Vector2 m_CurLookAt;	// 카메라가 봐야 하는 보정 위치
	CObject* m_targetObj;	// 카메라 타겟 오브젝트

	Vector2 m_Diff;			// 해상도 중심좌표와 LookAt의 좌표 차이값
	float m_time;			// 타겟을 따라가는데 걸리는 시간
	float m_speed;			// 타겟을 따라가는 속도
	float m_accTime;		// 누적 시간

public:
	void Update();
	void CalDiff();

public:
	void SetLookAt(Vector2 _look) { 
		m_LookAt = _look;
		float moveDist = (m_LookAt - m_PrevLookAt).Length();
		m_speed = moveDist / m_time;
		m_accTime = 0.f;
	}
	Vector2 GetLookAt() { return m_CurLookAt; }
	void SetTargetObj(CObject* _target) { m_targetObj = _target; }
	Vector2 GetRenderPos(Vector2 _vec) { return _vec - m_Diff; }
	Vector2 GetRealPos(Vector2 _vec) { return _vec + m_Diff; }
};
