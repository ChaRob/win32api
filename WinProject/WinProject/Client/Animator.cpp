#include "pch.h"
#include "Animator.h"
#include "Animation.h"

Animator::Animator():
	m_pOwner(nullptr), m_mapAnim{}, m_pCurAnim(nullptr)
{
}

Animator::~Animator()
{
	SafeDeleteMap(m_mapAnim);
}

void Animator::Update()
{
	if (m_pCurAnim != nullptr) {
		m_pCurAnim->Update();
	}
}

void Animator::Render(HDC _dc)
{
	if (m_pCurAnim != nullptr) {
		m_pCurAnim->Render(_dc);
	}
}

void Animator::CreateAnimation(const wstring& _animName, CTexture* _pTex, Vector2 _vLT, Vector2 _sliceSize, Vector2 _step, float _duration, UINT _frameCount)
{
	Animation* pAnim = FindAnimation(_animName);
	assert(pAnim == nullptr);

	pAnim = new Animation;

	pAnim->SetAnimName(_animName);
	pAnim->m_pAnimator = this;
	pAnim->Create(_pTex, _vLT, _sliceSize, _step, _duration, _frameCount);

	m_mapAnim.insert(make_pair(_animName, pAnim));
}

Animation* Animator::FindAnimation(const wstring& _animName)
{
	map<wstring, Animation*>::iterator iter = m_mapAnim.find(_animName);
	if (iter != m_mapAnim.end()) {
		return iter->second;
	}
	return nullptr;
}

void Animator::Play(const wstring& _animName)
{
	m_pCurAnim = FindAnimation(_animName);
	//assert(m_pCurAnim == nullptr);

}
