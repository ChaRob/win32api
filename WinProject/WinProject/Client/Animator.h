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
	CObject* m_pOwner;					// Animator ���� ������Ʈ
	map<wstring, Animation*> m_mapAnim;	// ��� Animation�� ���� ����
	Animation* m_pCurAnim;				// ���� ������� Animation
	bool m_repeat;						// �ݺ��������

public:
	void Update();
	void FinalUpdate();
	void Render(HDC _dc);

	void CreateAnimation(const wstring& _animName, CTexture* _pTex, Vector2 _vLT, Vector2 _sliceSize, Vector2 _step, float _duration, UINT _frameCount);
	Animation* FindAnimation(const wstring& _animName);
	void Play(const wstring& _animName, bool _repeat);
	CObject* GetOwnerObject() { return m_pOwner; }
};

