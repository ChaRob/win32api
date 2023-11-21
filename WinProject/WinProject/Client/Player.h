#pragma once
#include "CObject.h"

class Player : public CObject
{
public:
	virtual void Update();
	//virtual void Render(HDC _memDC);

private:
	void CreateMissile();
};

