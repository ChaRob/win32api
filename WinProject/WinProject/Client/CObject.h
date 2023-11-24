#pragma once

class Collider;
class Animator;
/*
	ȭ�鿡 �����ϴ� ��� ��ü Ŭ����
*/
class CObject
{
	friend class EventMgr;
private:
	Vector2 m_pos;
	Vector2 m_size;

	Collider* m_pCollider;
	wstring m_strName;
	bool	m_bAlive;
	Animator* m_animator;

public:
	CObject();
	CObject(const CObject& _origin);
	virtual ~CObject(); // �ڽ� �Ҹ��ڰ� ȣ��� �� �ֵ��� �����Լ��� ����
	virtual void Update() = 0;
	virtual void FinalUpdate() final;
	virtual void Render(HDC _memDC);

	virtual void OnCollision(Collider* _pOther);
	virtual void OnCollisionEnter(Collider* _pOther);
	virtual void OnCollisionExit(Collider* _pOther);

	virtual CObject* Clone() = 0;

public:
	void SetPos(Vector2 _vPos) { m_pos = _vPos; }
	void SetScale(Vector2 _vScale) { m_size = _vScale; }
	Vector2 GetPos() { return m_pos; }
	Vector2 GetScale() { return m_size; }
	void CreateCollider();
	void ComponentRender(HDC _memDC);
	Collider* GetCollider() { return m_pCollider; }
	const wstring& GetName() { return m_strName; }
	void SetName(const wstring& _str) { m_strName = _str; }
	bool IsDead() { return !m_bAlive; }

	void CreateAnimator();
	Animator* GetAnimator() { return m_animator; }

private:
	void SetDead() { m_bAlive = false; }
};