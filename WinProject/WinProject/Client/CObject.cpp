#include "pch.h"
#include "CObject.h"
#include "Collider.h"

CObject::CObject() :
	m_pos{}, m_size{}, m_pCollider(nullptr),
	m_strName(L""), m_bAlive(true)
{
}

CObject::~CObject()
{
	if (m_pCollider != nullptr) {
		delete m_pCollider;
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
	Rectangle(_memDC,
		(int)(m_pos.x - m_size.x / 2.f),
		(int)(m_pos.y - m_size.y / 2.f),
		(int)(m_pos.x + m_size.x / 2.f),
		(int)(m_pos.y + m_size.y / 2.f));

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
}
