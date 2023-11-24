#pragma once
#include "CObject.h"

class Monster : public CObject
{
public:
	Monster();
	~Monster();
	virtual void Update();
	Monster* Clone() { return new Monster(*this); }

private:
	float m_fSpeed;
	Vector2 m_CenterPos;
	float m_MaxDistance;
	int m_dir;

public:
	float GetSpeed() { return m_fSpeed; }
	void SetSpeed(float _speed) { m_fSpeed = _speed; }
	void SetCenterPos(Vector2 _vPos) { m_CenterPos = _vPos; }
	void SetMaxDistance(float _dis) { m_MaxDistance = _dis; }

	virtual void OnCollision(Collider* _pOther);
	virtual void OnCollisionEnter(Collider* _pOther);
	virtual void OnCollisionExit(Collider* _pOther);
};

