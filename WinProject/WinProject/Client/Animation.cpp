#include "pch.h"
#include "Animation.h"
#include "Animator.h"
#include "CObject.h"
#include "CTimeMgr.h"

Animation::Animation() :
	m_animName(L""), m_pAnimator(nullptr),
	m_pTex(nullptr), m_vecFram{}, m_CurFrame(0)
{
}

Animation::~Animation()
{
}

void Animation::Update()
{
	m_tACC += DeltaTimef;
	if (m_tACC > m_vecFram[m_CurFrame].duration) {
		m_CurFrame++;
		m_tACC = 0;
		if (m_CurFrame >= m_vecFram.size()) {
			m_CurFrame = 0;
		}
	}
}

void Animation::Render(HDC _dc)
{
	CObject* pObj = m_pAnimator->GetOwnerObject();
	Vector2 pPos = pObj->GetPos();

	TransparentBlt(_dc,
		(int)(pPos.x - m_vecFram[m_CurFrame].vSlice.x / 2.f),
		(int)(pPos.y - m_vecFram[m_CurFrame].vSlice.y / 2.f),
		(int)(m_vecFram[m_CurFrame].vSlice.x),
		(int)(m_vecFram[m_CurFrame].vSlice.y),
		m_pTex->GetDC(),
		(int)(m_vecFram[m_CurFrame].vLT.x),
		(int)(m_vecFram[m_CurFrame].vLT.y),
		(int)(m_vecFram[m_CurFrame].vSlice.x),
		(int)(m_vecFram[m_CurFrame].vSlice.y),
		RGB(255, 0, 255)
	);
}

void Animation::Create(CTexture* _pTex, Vector2 _vLT, Vector2 _sliceSize, Vector2 _step, float _duration, UINT _frameCount)
{
	m_pTex = _pTex;
	AnimFrame frm = {};
	for (UINT i = 0; i < _frameCount; i++)
	{
		frm.duration = _duration;
		frm.vSlice = _sliceSize;
		frm.vLT = _vLT + _step * (int)i;

		m_vecFram.push_back(frm);
	}
}
