#pragma once

class CObject;

class Collider
{
	friend class CObject;
public:
	Collider();
	Collider(const Collider& _origin);
	~Collider();
	// ���� �����ڸ� �۵���Ű�� �ʵ��� ����ϱ� ���� 
	// �ش� �Լ��� ����(delete), ���� ������ ����
	Collider& operator=(Collider& _origin) = delete;

private:
	CObject* m_pOwner;		// Collider�� �����ϰ� �ִ� ������Ʈ
	Vector2 m_offsetPos;	// ������Ʈ�κ��� ������� ��ġ
	Vector2 m_finalPos;		// FinalUpdate���� �� �����Ӹ��� ���� Collider�� ��ġ
	Vector2 m_size;			// Collider�� ũ��
	UINT m_ID;				// Collider�� ���� ������ ID ��
	static UINT s_nextID;	// Collider�� ������ ID ���� ������ ���������� ����

public:
	void FinalUpdate();
	void Render(HDC _memDc);
	void SetOffsetPos(const Vector2& _offset) { m_offsetPos = _offset; }
	void SetSize(const Vector2& _size) { m_size = _size; }
	Vector2& GetOffsetPos() { return m_offsetPos; }
	Vector2& GetSize() { return m_size; }
	UINT GetID() { return m_ID; }
	Vector2& GetFinalPos() { return m_finalPos; }
	CObject* GetOwnerObject() { return m_pOwner; }

public:
	void OnCollision(Collider* _pOther);		// �浹���� ��� ȣ��Ǵ� �Լ�
	void OnCollisionEnter(Collider* _pOther);	// �浹�� ��� ȣ��Ǵ� �Լ�
	void OnCollisionExit(Collider* _pOther);	// �浹�� ���� ��� ȣ��Ǵ� �Լ�
};

