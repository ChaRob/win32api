#include "pch.h"
#include "SceneTool.h"
#include "CKeyMgr.h"
#include "Tile.h"
#include "Camera.h"
#include "ResourceMgr.h"
#include "resource.h"
#include "SceneMgr.h"
#include "UI.h"
#include "Panel.h"
#include "Button.h"

SceneTool::SceneTool()
{
}

SceneTool::~SceneTool()
{
}

void SceneTool::Update()
{
	CScene::Update();

	SetTileIdx();
}

void SceneTool::Enter()
{
	// 타일 생성
	CreateTile(5, 5);

	Vector2 vResolution = CCore::GetInstance()->GetResolution();
	Camera::GetInstance()->SetLookAt(vResolution / 2);

	// UI 생성
	/*UI* ui = new UI(false);
	ui->SetName(L"ParentUI");
	ui->SetScale(Vector2{200.f, 100.f});
	ui->SetPos(Vector2{vResolution.x - ui->GetScale().x, 0.f});
	
	UI* newUI = new UI(false);
	newUI->SetName(L"ChildUI");
	newUI->SetScale(Vector2{ 100.f, 40.f });
	newUI->SetPos(Vector2{ 0.f, 0.f });
	
	ui->AddChildUI(newUI);
	AddObject(ui, GROUP_TYPE::UI);*/

	UI* PanelUI = new Panel;
	PanelUI->SetName(L"Panel");
	PanelUI->SetScale(Vector2{ 200.f, 100.f });
	PanelUI->SetPos(Vector2{ vResolution.x - PanelUI->GetScale().x, 0.f });

	UI* ButtonUI = new Button;
	ButtonUI->SetName(L"Button");
	ButtonUI->SetScale(Vector2{ 80.f, 50.f });
	ButtonUI->SetPos(Vector2{ 0.f, 0.f });

	PanelUI->AddChildUI(ButtonUI);
	AddObject(PanelUI, GROUP_TYPE::UI);

	UI* pClonePanel = PanelUI->Clone();
	pClonePanel->SetPos(pClonePanel->GetPos() + Vector2(-50.f, 0.f));
	AddObject(pClonePanel, GROUP_TYPE::UI);
}

void SceneTool::Exit()
{
}

void SceneTool::SetTileIdx()
{
	if (KEY_TAP(KEY::LMBTN)) {
		Vector2 mousePos = MOUSE_POS;
		mousePos = Camera::GetInstance()->GetRealPos(mousePos);

		// 가로 세로 인덱스 수를 가져온다.
		UINT tileX = GetTileX();
		UINT tileY = GetTileY();

		UINT col = (int)mousePos.x / TILE_SIZE;
		UINT row = (int)mousePos.y / TILE_SIZE;

		if (col >= tileX || mousePos.x < 0) return;
		if (row >= tileY || mousePos.y < 0) return;

		UINT targetidx = row * tileX + col;

		const vector<CObject*>& tiles = GetGroupObject(GROUP_TYPE::TILE);
		if (tiles.size() > targetidx) {
			((Tile*)tiles[targetidx])->AddImgIdx();
		}
	}
}


/*
	Tile Count Window Proc
	
	CALLBACK => __stdcall : 함수 호출 규약
	보통 Window API에서 많이 사용한다. 다음과 같은 특징이 있다.
	
	1. 인자 전달 순서: 함수의 매개변수는 오른쪽에서 왼쪽으로 전달됩니다.
	예를 들어, MyFunction(1, 2)라면 스택에는 먼저 2가 푸시되고, 그 다음에 1이 푸시됩니다.

	2. 스택 정리: 호출자(caller)가 스택을 정리합니다. 즉, 함수가 종료되면 호출자가 스택 상의 함수의 매개변수를 제거합니다.

	3. 함수 이름 데코레이션: 함수의 이름 끝에 @n이라는 형태의 접미사가 추가됩니다. 여기서 n은 함수에 전달된 바이트 수입니다.
*/
INT_PTR CALLBACK TileCount(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			UINT m = GetDlgItemInt(hwnd, IDC_EDIT1, nullptr, false);
			UINT n = GetDlgItemInt(hwnd, IDC_EDIT2, nullptr, false);

			CScene* pCurScene = SceneMgr::GetInstance()->GetCurScene();
			
			// dynamic_cast를 사용해서 캐스팅
			// 만약 실패하면 nullptr이 나온다.
			SceneTool* pToolScene = dynamic_cast<SceneTool*>(pCurScene);

			if (pToolScene != nullptr) {
				pToolScene->DeleteGroup(GROUP_TYPE::TILE);
				pToolScene->CreateTile(m,n);
			}

			EndDialog(hwnd, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			// EndDialog를 할 때, 두번째 인자로 결과값을 전달해준다.
			EndDialog(hwnd, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}