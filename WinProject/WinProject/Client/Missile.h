#pragma once
#include "CObject.h"

class Missile : public CObject
{
public:
	Missile();
	~Missile();
	virtual void Update();
	virtual void Render(HDC _memDC);
	virtual void OnCollisionEnter(Collider* _pOther);


	Missile* Clone() { return new Missile(*this); }

private:
	Vector2 m_dir; // 방향 지정

public:
	void SetDir(Vector2 _dir) { m_dir = _dir.Normalize(); }
};

