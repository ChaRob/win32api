#pragma once

// 1. 프레임 동기화
// 동일 프레임 내에서 같은 키에 대해, 동일한 이벤트를 가져간다.

// 2. 키 입력 이벤트 처리
// tap, hold, away

enum class KEY_STATE
{
	KEY_NONE, // 아무 변화가 없음
	KEY_TAP,  // 막 누른 시점
	KEY_HOLD, // 누르고 있는
	KEY_AWAY, // 막 뗀 시점
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q, W, E, R, T, Y, U, I, O, P,
	A, S, D, F, G, H, J, K, L,
	Z, X, C, V, B, N, M,
	ALT,
	LSHIFT,
	SPACE,
	CTRL,
	ENTER,
	ESC,

	LAST, // enum의 끝
};

struct KeyInfo {
	KEY_STATE	eState; // 키상태값
	bool		bPrev;	// 이전에 해당 키가 눌렸는지 판단
};

class CKeyMgr
{
	SINGLE(CKeyMgr);
private:
	vector<KeyInfo> m_vecKey;
	
public:
	void Init();
	void Update();
	KEY_STATE GetKeyState(KEY _key);
};

