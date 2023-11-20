#pragma once

// 1. ������ ����ȭ
// ���� ������ ������ ���� Ű�� ����, ������ �̺�Ʈ�� ��������.

// 2. Ű �Է� �̺�Ʈ ó��
// tap, hold, away

enum class KEY_STATE
{
	KEY_NONE, // �ƹ� ��ȭ�� ����
	KEY_TAP,  // �� ���� ����
	KEY_HOLD, // ������ �ִ�
	KEY_AWAY, // �� �� ����
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

	LAST, // enum�� ��
};

struct KeyInfo {
	KEY_STATE	eState; // Ű���°�
	bool		bPrev;	// ������ �ش� Ű�� ���ȴ��� �Ǵ�
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

