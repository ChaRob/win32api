#pragma once
#include "CObject.h"

class Monster : public CObject
{
public:
	Monster();
	~Monster();

private:
	float m_fSpeed;
	Vector2 m_CenterPos;
	float m_MaxDistance;
	int m_dir;

public:
	virtual void Update();
	float GetSpeed() { return m_fSpeed; }
	void SetSpeed(float _speed) { m_fSpeed = _speed; }
	void SetCenterPos(Vector2 _vPos) { m_CenterPos = _vPos; }
	void SetMaxDistance(float _dis) { m_MaxDistance = _dis; }
};

