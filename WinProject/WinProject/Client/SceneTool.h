#pragma once
#include "CScene.h"

class SceneTool : public CScene
{
public:
	SceneTool();
	~SceneTool();

private:


public:
	virtual void Update();
	virtual void Enter();
	virtual void Exit();

public:
	void SetTileIdx();
	void SaveData(const wstring& _strFilePath);
	void SaveFile();
	void LoadFile();
};

