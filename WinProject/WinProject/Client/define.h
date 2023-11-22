#pragma once

//
// ��ũ���Լ�, ��ó���⿡ ���� �Լ��� ȣ���ϴ� ����ó�� ���
// ���������� ġȯ�ϴ� �����̱� ������, ġȯ�� �� ��� �����ϴ��� �׻� ������ ��.
//

// �̱��� ��ũ���Լ�
#define SINGLE(type) public:\
							 static type* GetInstance()\
							 {\
								static type mgr;\
								return &mgr;\
							 }\
					private:\
							type();\
							~type();

// deltaTime ����ȭ
#define DeltaTime CTimeMgr::GetInstance()->GetDeltaTime()
#define DeltaTimef CTimeMgr::GetInstance()->GetDeltaTimef()

#define PI 3.14159265358979323846

enum class GROUP_TYPE
{
	DEFALUT,
	PLAYER,
	MISSILE,
	MONSTER,

	END,
};

enum class SCENE_TYPE
{
	TOOL,

	START,
	STAGE_1, STAGE_2, STAGE_3,

	END,
};

#define KEY_CHECK(key, state) CKeyMgr::GetInstance()->GetKeyState(key) == state
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::KEY_HOLD)
#define KEY_TAP(key)  KEY_CHECK(key, KEY_STATE::KEY_TAP)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::KEY_AWAY)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::KEY_NONE)

enum class BRUSH_TYPE {

	HOLLOW,
	END
};

enum class PEN_TYPE {
	RED,
	GREEN,
	BLUE,
	END
};