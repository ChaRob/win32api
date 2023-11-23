#include "pch.h"
#include "CTimeMgr.h"
#include <tchar.h>

CTimeMgr::CTimeMgr() :m_llCurCounter{}, m_llPrevCounter{}, m_llFrequency {},
					  deltaTime(0), m_callcount(0) {}
CTimeMgr::~CTimeMgr() {}

void CTimeMgr::Init()
{
	QueryPerformanceCounter(&m_llPrevCounter);	// GetTickCount�� �Ȱ��� ���, ������ 1�鸸
	QueryPerformanceFrequency(&m_llFrequency);	// �ʴ� ī��Ʈ �� ���̰� ������ �˷��ش�.
}

// delta time update
void CTimeMgr::Update()
{
	QueryPerformanceCounter(&m_llCurCounter);

	// ������ ���ݴ� ���ܳ� count ���̰��� ����
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
