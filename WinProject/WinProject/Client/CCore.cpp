#include "pch.h"
#include "CCore.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "SceneMgr.h"
#include "PathManager.h"
#include "CollisionMgr.h"

CCore::CCore():
	m_hwnd(0),
	m_ptResolution{},
	m_hDC(0),
	m_hBit(0),
	m_memDC(0),
	m_arrBrush{},
	m_arrPen{}
{}
CCore::~CCore()
{
	ReleaseDC(m_hwnd, m_hDC);
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);

	for (UINT i = 0; i < (UINT)PEN_TYPE::END; i++)
	{
		DeleteObject(m_arrPen[i]);
		//delete m_arrPen[i];
	}
}

int CCore::Init(HWND _hwnd, POINT _ptResolution)
{
	m_hwnd = _hwnd;
	m_ptResolution = _ptResolution;

	// 해상도에 맞게 윈도우 크기 조절
	// window 7, 10에 따라서 경게(border)가 다르기에 지정한 해상도가 나오도록 잡아준다.
	RECT rt = {0, 0, m_ptResolution.x, m_ptResolution.y};
	AdjustWindowRect(
		&rt, /* LPRECT, 곧 RECT*를 의미. 함수가 종료되면 rt에 저장된 값을 접근해서 수정해줌. */
		WS_OVERLAPPEDWINDOW, /* 자주 쓰는 윈도우 세팅을 합쳐둔 것 */
		TRUE);
	SetWindowPos(m_hwnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	// Device Context 초기화 및 호출
	// 메세지 기반 방식이 아닌, 우리가 원할 때 그림을 그릴 수 있도록 설정함.
	m_hDC = GetDC(m_hwnd);

	// 이중 버퍼링 용도의 비트맵과 DC 생성
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y); // 기존 DC와 호환성 있는 동작이 가능하도록 한 함수
	m_memDC = CreateCompatibleDC(m_hDC);

	// m_memDC가 기존에 가리키고 있던 bitmap은 사용하지 않으므로 제거한다.
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);

	// 자주 사용할 브러쉬와 펜을 등록
	CreateBrushPen();

	// Manager 초기화
	PathManager::GetInstance()->Init();
	CKeyMgr::GetInstance()->Init();
	CTimeMgr::GetInstance()->Init();
	SceneMgr::GetInstance()->Init();
	CollisionMgr::GetInstance()->Init();

	return S_OK;
}

void CCore::Progress()
{
	// Manager Update
	CTimeMgr::GetInstance()->Update();
	CKeyMgr::GetInstance()->Update();

	SceneMgr::GetInstance()->Update();
	CollisionMgr::GetInstance()->Update();
	// Update();
	// 그리기 작업
	// 게임 화면이라는 것은 매순간마다 계속 변화하는 과정.
	// 한 장면을 그리고 보여주고, 뒤에서 새로 그린 것을 다시 대체해서 보여주고...반복

	// 그리기 작업 전 화면 청소, 재구성
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	// Render();
	SceneMgr::GetInstance()->Render(m_memDC);

	// 다른 화면에서 그린 그림을 복사해서 그려준다.
	// 이 프로젝트(WinAPI)에서는 CPU가 rendering을 담당하지만, DirectX를 사용해서 GPU에게 이 일을 맡기면 속도를 더 늘릴 수 있다.
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_memDC, 0, 0, SRCCOPY);

	// CTimeMgr::GetInstance()->render();
}

void CCore::CreateBrushPen()
{
	// Brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);


	// Pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 이 아래는 학습용으로 지금은 사용하지 않음.
/*
void CCore::Update()
{
	// 비동기 키 입출력 함수
	// 윈도우가 활성화되어 있지 않아도 동작하기 때문에, 신경써야함.
	Vector2 newPos = g_object.GetPos();

	//if (GetAsyncKeyState(VK_LEFT) & 0x8000) // 눌렸는지 체크하는 방식.
	if (CKeyMgr::GetInstance()->GetKeyState(KEY::LEFT) == KEY_STATE::KEY_HOLD) // 눌렸는지 체크하는 방식.
	{
		// 컴퓨터 설정에 따라서 호출하는 함수의 횟수가 다르기 때문에,
		// 숫자값을 조정하는 것으로는 해결하는게 말이 되지 않는다.
		// 멀티플레이 게임을 생각해보자.
		// 따라서 모든 컴퓨터의 성능에 상관없이, 일정한 함수 호출(또는 이동량)을 보장해야 한다.
		newPos.x -= 100 * DeltaTime;
	}
	if (CKeyMgr::GetInstance()->GetKeyState(KEY::RIGHT) == KEY_STATE::KEY_HOLD) // 눌렸는지 체크하는 방식.
	{
		newPos.x += 100 * DeltaTime;
	}
	if (CKeyMgr::GetInstance()->GetKeyState(KEY::UP) == KEY_STATE::KEY_HOLD) // 눌렸는지 체크하는 방식.
	{
		newPos.y -= 100 * DeltaTime;
	}
	if (CKeyMgr::GetInstance()->GetKeyState(KEY::DOWN) == KEY_STATE::KEY_HOLD) // 눌렸는지 체크하는 방식.
	{
		newPos.y += 100 * DeltaTime;
	}

	g_object.SetPos(newPos);
}

void CCore::Render()
{

	Vector2 vPos = g_object.GetPos();
	Vector2 vScale = g_object.GetScale();

	Rectangle(m_memDC, 
		int(vPos.x - vScale.x / 2.f),
		int(vPos.y - vScale.y / 2.f),
		int(vPos.x + vScale.x / 2.f),
		int(vPos.y + vScale.y / 2.f));

}
*/