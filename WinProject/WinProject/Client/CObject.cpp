#include "pch.h"
#include "CObject.h"
#include "Collider.h"
#include "Animator.h"
#include "Camera.h"

CObject::CObject() :
	m_pos{}, m_size{}, m_pCollider(nullptr),
	m_strName(L""), m_bAlive(true), m_animator(nullptr)
{
}

CObject::CObject(const CObject& _origin) :
	m_pos(_origin.m_pos), m_size(_origin.m_size), m_pCollider(nullptr),
	m_strName(_origin.m_strName), m_bAlive(true), m_animator(nullptr)
{
	// 오브젝트를 복사할 때, 얕은 복사가 아닌 깊은 복사를 하기 위해
	// 충돌체를 직접 복사해준다.
	if (_origin.m_pCollider != nullptr) {
		m_pCollider = new Collider(*_origin.m_pCollider);
		m_pCollider->m_pOwner = this;
	}

	if (_origin.m_animator != nullptr) {
		m_animator = new Animator(*_origin.m_animator);
		m_animator->m_pOwner = this;
	}
}

CObject::~CObject()
{
	if (m_pCollider != nullptr) {
		delete m_pCollider;
	}

	if (m_animator != nullptr) {
		delete m_animator;
	}
}

void CObject::Update()
{
}

void CObject::FinalUpdate()
{
	if (m_pCollider != nullptr) {
		m_pCollider->FinalUpdate();
	}
}

void CObject::Render(HDC _memDC)
{
	Vector2 renderPos = Camera::GetInstance()->GetRenderPos(m_pos);

	Rectangle(_memDC,
		(int)(renderPos.x - m_size.x / 2.f),
		(int)(renderPos.y - m_size.y / 2.f),
		(int)(renderPos.x + m_size.x / 2.f),
		(int)(renderPos.y + m_size.y / 2.f));

	ComponentRender(_memDC);
}

void CObject::OnCollision(Collider* _pOther)
{

}

void CObject::OnCollisionEnter(Collider* _pOther)
{

}

void CObject::OnCollisionExit(Collider* _pOther)
{

}

void CObject::CreateCollider()
{
	m_pCollider = new Collider;
	m_pCollider->m_pOwner = this;
}

void CObject::ComponentRender(HDC _memDC)
{
	if (m_pCollider != nullptr) {
		m_pCollider->Render(_memDC);
	}

	if (m_animator != nullptr) {
		m_animator->Render(_memDC);
	}
}

void CObject::CreateAnimator()
{
	m_animator = new Animator();
	m_animator->m_pOwner = this;
}
