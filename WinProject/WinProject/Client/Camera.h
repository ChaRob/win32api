#pragma once
#include "CObject.h"

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE
};

struct camEffect {
	CAM_EFFECT m_effect;		// 카메라 효과
	float m_duration;		// 효과 진행 시간
	float m_accDuration;	// 효과 진행중인 시간
};

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

	CTexture* m_pVeilTex;	// 가림막 텍스쳐(검은색)

	queue<camEffect> m_vecCamEffect;

public:
	void Init();
	void Update();
	void CalDiff();
	void Render(HDC _dc);

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
	void FadeIn(float _duration) 
	{ 
		camEffect ef = {};
		ef.m_effect = CAM_EFFECT::FADE_IN; 
		ef.m_duration = _duration;
		if (ef.m_duration == 0.f) ef.m_duration = 0.01f;
		m_vecCamEffect.push(ef);
	}
	void FadeOut(float _duration) 
	{
		camEffect ef = {};
		ef.m_effect = CAM_EFFECT::FADE_OUT;
		ef.m_duration = _duration;
		if (ef.m_duration == 0.f) ef.m_duration = 0.01f;
		m_vecCamEffect.push(ef);
	}
};
