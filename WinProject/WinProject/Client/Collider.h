#pragma once

class CObject;

class Collider
{
	friend class CObject;
public:
	Collider();
	~Collider();

private:
	CObject* m_pOwner;		// Collider�� �����ϰ� �ִ� ������Ʈ
	Vector2 m_offsetPos;	// ������Ʈ�κ��� ������� ��ġ
	Vector2 m_finalPos;		// FinalUpdate���� �� �����Ӹ��� ���� Collider�� ��ġ
	Vector2 m_size;			// Collider�� ũ��
public:
	void FinalUpdate();
	void Render(HDC _memDc);
	void SetOffsetPos(const Vector2& _offset) { m_offsetPos = _offset; }
	void SetSize(const Vector2& _size) { m_size = _size; }
	Vector2& GetOffsetPos() { return m_offsetPos; }
	Vector2& GetSize() { return m_size; }
};

