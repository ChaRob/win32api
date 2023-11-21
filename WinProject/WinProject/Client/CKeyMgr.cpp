#include "pch.h"
#include "CKeyMgr.h"
#include "CCore.h"

int g_arrVK[(int)KEY::LAST] = {
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,
	'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
	'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
	'Z', 'X', 'C', 'V', 'B', 'N', 'M',
	VK_MENU,
	VK_LSHIFT,
	VK_SPACE,
	VK_CONTROL,
	VK_RETURN,
	VK_ESCAPE,
};

CKeyMgr::CKeyMgr() {}
CKeyMgr::~CKeyMgr() {}

void CKeyMgr::Init()
{
	for (int i = 0; i < (int)KEY::LAST; i++)
	{
		m_vecKey.push_back(KeyInfo{ KEY_STATE::KEY_NONE, false });
	}
}

void CKeyMgr::Update()
{
	// 현재 윈도우 창을 포커싱중인지 확인
	// HWND hMainWnd = CCore::GetInstance()->GetMainHwnd();
	HWND hWnd = GetFocus();
	if (hWnd == nullptr) {
		for (int i = 0; i < (int)KEY::LAST; i++)
		{
			m_vecKey[i].bPrev = false;
			if (m_vecKey[i].eState == KEY_STATE::KEY_TAP || m_vecKey[i].eState == KEY_STATE::KEY_HOLD) {
				m_vecKey[i].eState = KEY_STATE::KEY_AWAY;
			}
			else {
				m_vecKey[i].eState = KEY_STATE::KEY_NONE;
			}
		}
		return;
	}

	// 키 상태 체크
	for (int i = 0; i < (int)KEY::LAST; i++)
	{
		if (GetAsyncKeyState(g_arrVK[i]) & 0x8000) {
			if (m_vecKey[i].bPrev) {
				m_vecKey[i].eState = KEY_STATE::KEY_HOLD;
			}
			else {
				m_vecKey[i].eState = KEY_STATE::KEY_TAP;
			}

			m_vecKey[i].bPrev = true;
		}
		else {
			if (m_vecKey[i].bPrev) {
				m_vecKey[i].eState = KEY_STATE::KEY_AWAY;
			}
			else {
				m_vecKey[i].eState = KEY_STATE::KEY_NONE;
			}
			m_vecKey[i].bPrev = false;
		}
	}
}

KEY_STATE CKeyMgr::GetKeyState(KEY _key)
{
	return m_vecKey[(int)_key].eState;
}
