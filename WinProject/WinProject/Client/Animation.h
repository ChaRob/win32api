#pragma once
#include "CTexture.h"
#include "global.h"

struct AnimFrame {
	Vector2 vLT;
	Vector2 vSlice;
	Vector2 offset;
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
	bool m_isFinish;				// ���� �ִϸ��̼��� ��������� Ȯ���ϴ� ����

public:
	void Update();
	void Render(HDC _dc);
	const wstring& GetAnimName() { return m_animName; }
	void Create(CTexture* _pTex, Vector2 _vLT, Vector2 _sliceSize, Vector2 _step, float _duration, UINT _frameCount);
	bool IsFinish() { return m_isFinish; }
	void SetFrame(int _frameIdx) {
		m_isFinish = false;
		m_CurFrame = _frameIdx;
		m_tACC = 0.f;
	}
	AnimFrame& GetFrame(int _frameIdx) { return m_vecFram[_frameIdx]; }
	const size_t GetMaxFrame() { return m_vecFram.size(); }

private:
	void SetAnimName(const wstring& _animName) { m_animName = _animName; }
};

