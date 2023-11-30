#pragma once
#include "CObject.h"

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE
};

struct camEffect {
	CAM_EFFECT m_effect;		// ī�޶� ȿ��
	float m_duration;		// ȿ�� ���� �ð�
	float m_accDuration;	// ȿ�� �������� �ð�
};

class Camera
{
	SINGLE(Camera);
private:
	Vector2 m_LookAt;		// ���� ī�޶� ���� �ִ� ��ġ => ���� ��ǥ
	Vector2 m_PrevLookAt;	// ī�޶� ���� ���� ������ ��ġ
	Vector2 m_CurLookAt;	// ī�޶� ���� �ϴ� ���� ��ġ
	CObject* m_targetObj;	// ī�޶� Ÿ�� ������Ʈ

	Vector2 m_Diff;			// �ػ� �߽���ǥ�� LookAt�� ��ǥ ���̰�
	float m_time;			// Ÿ���� ���󰡴µ� �ɸ��� �ð�
	float m_speed;			// Ÿ���� ���󰡴� �ӵ�
	float m_accTime;		// ���� �ð�

	CTexture* m_pVeilTex;	// ������ �ؽ���(������)

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
