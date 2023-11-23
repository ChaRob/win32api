#include "pch.h"
#include "CTimeMgr.h"
#include <tchar.h>

CTimeMgr::CTimeMgr() :m_llCurCounter{}, m_llPrevCounter{}, m_llFrequency {},
					  deltaTime(0), m_callcount(0) {}
CTimeMgr::~CTimeMgr() {}

void CTimeMgr::Init()
{
	QueryPerformanceCounter(&m_llPrevCounter);	// GetTickCount와 똑같은 기능, 단위는 1백만
	QueryPerformanceFrequency(&m_llFrequency);	// 초당 카운트 값 차이가 얼마인지 알려준다.
}

// delta time update
void CTimeMgr::Update()
{
	QueryPerformanceCounter(&m_llCurCounter);

	// 프레임 간격당 생겨난 count 차이값을 구함
	deltaTime = (double)(m_llCurCounter.QuadPart - m_llPrevCounter.QuadPart) / (double)m_llFrequency.QuadPart;
	m_llPrevCounter = m_llCurCounter;

#ifdef _DEBUG
	if (deltaTime > 1.0 / 60.0)
		deltaTime = 1.0 / 60.0;
#endif // DEBUG
}

void CTimeMgr::render()
{
	m_callcount++;
	timeAcc += deltaTime;
	if (timeAcc >= 1.0) {
		m_FPS = m_callcount;
		m_callcount = 0;
		timeAcc = 0;

		wchar_t szBuffer[255] = {};

		swprintf_s(szBuffer, L"FPS : %d, DT : %f", m_FPS, deltaTime);
		SetWindowText(CCore::GetInstance()->GetMainHwnd(), szBuffer);
	}
}
