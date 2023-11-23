#include "pch.h"
#include "SceneTool.h"
#include "CKeyMgr.h"

SceneTool::SceneTool()
{
}

SceneTool::~SceneTool()
{
}

//void SceneTool::Update()
//{
//	// CScene::Update();
//}

void SceneTool::Update()
{
	if (KEY_TAP(KEY::ENTER)) {
		ChangeScene(SCENE_TYPE::START);
	}
}

void SceneTool::Enter()
{
}

void SceneTool::Exit()
{
}
