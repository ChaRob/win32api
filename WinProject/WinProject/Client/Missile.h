#pragma once
#include "CObject.h"

class Missile : public CObject
{
public:
	Missile();
	~Missile();

private:
	Vector2 m_dir; // 방향 지정

public:
	virtual void Update();
	virtual void Render(HDC _memDC);
	virtual void OnCollisionEnter(Collider* _pOther);
	void SetDir(Vector2 _dir) { m_dir = _dir.Normalize(); }
};

