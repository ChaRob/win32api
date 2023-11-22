#pragma once

//
// 매크로함수, 전처리기에 의해 함수를 호출하는 형식처럼 사용
// 주의할점은 치환하는 형식이기 때문에, 치환될 때 어떻게 동작하는지 항상 유의할 것.
//

// 싱글톤 매크로함수
#define SINGLE(type) public:\
							 static type* GetInstance()\
							 {\
								static type mgr;\
								return &mgr;\
							 }\
					private:\
							type();\
							~type();

// deltaTime 간략화
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