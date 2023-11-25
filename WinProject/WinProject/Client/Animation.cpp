#include "pch.h"
#include "Animation.h"
#include "Animator.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "Camera.h"

Animation::Animation() :
	m_animName(L""), m_pAnimator(nullptr),
	m_pTex(nullptr), m_vecFram{}, m_CurFrame(0),
	m_tACC(0.f), m_isFinish(false)
{
}

Animation::~Animation()
{
}

void Animation::Update()
{
	if (m_isFinish) return;

	m_tACC += DeltaTimef;
	if (m_tACC > m_vecFram[m_CurFrame].duration) {
		m_tACC -= m_vecFram[m_CurFrame].duration;
		m_CurFrame++;
		if (m_CurFrame >= m_vecFram.size()) {
			m_CurFrame = -1;
			m_isFinish = true;
		}
	}
}

void Animation::Render(HDC _dc)
{
	if (m_isFinish) return;

	CObject* pObj = m_pAnimator->GetOwnerObject();
	Vector2 pPos = pObj->GetPos() + m_vecFram[m_CurFrame].offset;

	// 렌더링 좌표로 변환(카메라)
	pPos = Camera::GetInstance()->GetRenderPos(pPos);

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
