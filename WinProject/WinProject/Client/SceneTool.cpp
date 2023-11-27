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
	// Ÿ�� ����
	CreateTile(5, 5);

	Vector2 vResolution = CCore::GetInstance()->GetResolution();
	Camera::GetInstance()->SetLookAt(vResolution / 2);

	// UI ����
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

		// ���� ���� �ε��� ���� �����´�.
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
	
	CALLBACK => __stdcall : �Լ� ȣ�� �Ծ�
	���� Window API���� ���� ����Ѵ�. ������ ���� Ư¡�� �ִ�.
	
	1. ���� ���� ����: �Լ��� �Ű������� �����ʿ��� �������� ���޵˴ϴ�.
	���� ���, MyFunction(1, 2)��� ���ÿ��� ���� 2�� Ǫ�õǰ�, �� ������ 1�� Ǫ�õ˴ϴ�.

	2. ���� ����: ȣ����(caller)�� ������ �����մϴ�. ��, �Լ��� ����Ǹ� ȣ���ڰ� ���� ���� �Լ��� �Ű������� �����մϴ�.

	3. �Լ� �̸� ���ڷ��̼�: �Լ��� �̸� ���� @n�̶�� ������ ���̻簡 �߰��˴ϴ�. ���⼭ n�� �Լ��� ���޵� ����Ʈ ���Դϴ�.
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
			
			// dynamic_cast�� ����ؼ� ĳ����
			// ���� �����ϸ� nullptr�� ���´�.
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
			// EndDialog�� �� ��, �ι�° ���ڷ� ������� �������ش�.
			EndDialog(hwnd, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}