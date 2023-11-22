#pragma once
class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER m_llCurCounter;
	LARGE_INTEGER m_llPrevCounter;
	LARGE_INTEGER m_llFrequency;

	// FPS : 1������ �� �ð� => Delta Time
	double deltaTime;
	double timeAcc;
	UINT m_callcount;	// update ȣ��Ƚ�� => FPS�� ���� ���� count
	UINT m_FPS;			// �ʴ� ȣ�� Ƚ��(FPS)

public:
	void Init();
	void Update();
	void render();
	double GetDeltaTime() { return deltaTime; }
	float GetDeltaTimef() { return (float)deltaTime; }
};

