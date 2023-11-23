#pragma once

class CObject;

class Collider
{
	friend class CObject;
public:
	Collider();
	Collider(const Collider& _origin);
	~Collider();
	// 대입 연산자를 작동시키지 않도록 방어하기 위해 
	// 해당 함수를 제거(delete), 대입 연산을 방지
	Collider& operator=(Collider& _origin) = delete;

private:
	CObject* m_pOwner;		// Collider를 소유하고 있는 오브젝트
	Vector2 m_offsetPos;	// 오브젝트로부터 상대적인 위치
	Vector2 m_finalPos;		// FinalUpdate에서 매 프레임마다 계산된 Collider의 위치
	Vector2 m_size;			// Collider의 크기
	UINT m_ID;				// Collider가 갖는 고유한 ID 값
	static UINT s_nextID;	// Collider가 고유한 ID 값을 갖도록 정적변수를 생성

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
	void OnCollision(Collider* _pOther);		// 충돌중인 경우 호출되는 함수
	void OnCollisionEnter(Collider* _pOther);	// 충돌한 경우 호출되는 함수
	void OnCollisionExit(Collider* _pOther);	// 충돌이 끝난 경우 호출되는 함수
};

