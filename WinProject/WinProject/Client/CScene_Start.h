#pragma once
#include "CScene.h"

class CScene_Start : public CScene
{
public:
	CScene_Start();
	~CScene_Start();

public:
	// 부모에서 상속받은 가상함수들 선언
	virtual void Update();
	virtual void Enter();
	virtual void Exit();
};

