#pragma once
#include "CTexture.h"

struct AnimFrame {
	Vector2 vLT;
	Vector2 vSlice;
	float duration;
};


class Animation
{
	friend class Animator;
public:
	Animation();
	~Animation();

private:
	wstring m_animName;
	Animator* m_pAnimator;
	CTexture* m_pTex;				// Animation�� ����ϴ� �ؽ���
	vector<AnimFrame> m_vecFram;	// ��� ������ ����
	int m_CurFrame;					// ���� ������ �ε��� ����
	float m_tACC;					// �ð� ������ ����

public:
	void Update();
	void Render(HDC _dc);
	const wstring& GetAnimName() { return m_animName; }
	void Create(CTexture* _pTex, Vector2 _vLT, Vector2 _sliceSize, Vector2 _step, float _duration, UINT _frameCount);

private:
	void SetAnimName(const wstring& _animName) { m_animName = _animName; }
};

