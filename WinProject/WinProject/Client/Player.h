#pragma once
#include "CObject.h"

class CTexture;

class Player : public CObject
{
public:
	Player();
	~Player();

public:
	virtual void Update();
	virtual void Render(HDC _memDC);

private:
	void CreateMissile();
	CTexture* m_pTex;
};

