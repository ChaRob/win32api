#pragma once

class CObject;
class Animation;
class CTexture;

class Animator
{
	friend class CObject;
public:
	Animator();
	~Animator();

private:
	CObject* m_pOwner;					// Animator 소유 오브젝트
	map<wstring, Animation*> m_mapAnim;	// 모든 Animation을 담은 변수
	Animation* m_pCurAnim;				// 현재 재생중인 Animation

public:
	void Update();
	void Render(HDC _dc);

	void CreateAnimation(const wstring& _animName, CTexture* _pTex, Vector2 _vLT, Vector2 _sliceSize, Vector2 _step, float _duration, UINT _frameCount);
	Animation* FindAnimation(const wstring& _animName);
	void Play(const wstring& _animName);
	CObject* GetOwnerObject() { return m_pOwner; }
};

