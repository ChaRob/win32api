#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER m_llCurCounter;
	LARGE_INTEGER m_llPrevCounter;
	LARGE_INTEGER m_llFrequency;

	// FPS : 1프레임 당 시간 => Delta Time
	double deltaTime;
	double timeAcc;
	UINT m_callcount;	// update 호출횟수 => FPS를 세기 위한 count
	UINT m_FPS;			// 초당 호출 횟수(FPS)

public:
	void Init();
	void Update();
	void render();
	double GetDeltaTime() { return deltaTime; }
	float GetDeltaTimef() { return (float)deltaTime; }
};

