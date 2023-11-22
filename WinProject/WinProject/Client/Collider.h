#pragma once

class CObject;

class Collider
{
	friend class CObject;
public:
	Collider();
	~Collider();

private:
	CObject* m_pOwner;		// Collider를 소유하고 있는 오브젝트
	Vector2 m_offsetPos;	// 오브젝트로부터 상대적인 위치
	Vector2 m_finalPos;		// FinalUpdate에서 매 프레임마다 계산된 Collider의 위치
	Vector2 m_size;			// Collider의 크기
public:
	void FinalUpdate();
	void Render(HDC _memDc);
	void SetOffsetPos(const Vector2& _offset) { m_offsetPos = _offset; }
	void SetSize(const Vector2& _size) { m_size = _size; }
	Vector2& GetOffsetPos() { return m_offsetPos; }
	Vector2& GetSize() { return m_size; }
};

