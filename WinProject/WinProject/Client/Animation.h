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
	CTexture* m_pTex;				// Animation에 사용하는 텍스쳐
	vector<AnimFrame> m_vecFram;	// 모든 프레임 정보
	int m_CurFrame;					// 현재 프레임 인덱스 정보
	float m_tACC;					// 시간 누적용 변수
	bool m_isFinish;				// 현재 애니메이션이 재생중인지 확인하는 변수

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

