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

	// �ػ󵵿� �°� ������ ũ�� ����
	// window 7, 10�� ���� ���(border)�� �ٸ��⿡ ������ �ػ󵵰� �������� ����ش�.
	RECT rt = {0, 0, m_ptResolution.x, m_ptResolution.y};
	AdjustWindowRect(
		&rt, /* LPRECT, �� RECT*�� �ǹ�. �Լ��� ����Ǹ� rt�� ����� ���� �����ؼ� ��������. */
		WS_OVERLAPPEDWINDOW, /* ���� ���� ������ ������ ���ĵ� �� */
		TRUE);
	SetWindowPos(m_hwnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	// Device Context �ʱ�ȭ �� ȣ��
	// �޼��� ��� ����� �ƴ�, �츮�� ���� �� �׸��� �׸� �� �ֵ��� ������.
	m_hDC = GetDC(m_hwnd);

	// ���� ���۸� �뵵�� ��Ʈ�ʰ� DC ����
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y); // ���� DC�� ȣȯ�� �ִ� ������ �����ϵ��� �� �Լ�
	m_memDC = CreateCompatibleDC(m_hDC);

	// m_memDC�� ������ ����Ű�� �ִ� bitmap�� ������� �����Ƿ� �����Ѵ�.
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);

	// ���� ����� �귯���� ���� ���
	CreateBrushPen();

	// Manager �ʱ�ȭ
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
	// �׸��� �۾�
	// ���� ȭ���̶�� ���� �ż������� ��� ��ȭ�ϴ� ����.
	// �� ����� �׸��� �����ְ�, �ڿ��� ���� �׸� ���� �ٽ� ��ü�ؼ� �����ְ�...�ݺ�

	// �׸��� �۾� �� ȭ�� û��, �籸��
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	// Render();
	SceneMgr::GetInstance()->Render(m_memDC);

	// �ٸ� ȭ�鿡�� �׸� �׸��� �����ؼ� �׷��ش�.
	// �� ������Ʈ(WinAPI)������ CPU�� rendering�� ���������, DirectX�� ����ؼ� GPU���� �� ���� �ñ�� �ӵ��� �� �ø� �� �ִ�.
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
// �� �Ʒ��� �н������� ������ ������� ����.
/*
void CCore::Update()
{
	// �񵿱� Ű ����� �Լ�
	// �����찡 Ȱ��ȭ�Ǿ� ���� �ʾƵ� �����ϱ� ������, �Ű�����.
	Vector2 newPos = g_object.GetPos();

	//if (GetAsyncKeyState(VK_LEFT) & 0x8000) // ���ȴ��� üũ�ϴ� ���.
	if (CKeyMgr::GetInstance()->GetKeyState(KEY::LEFT) == KEY_STATE::KEY_HOLD) // ���ȴ��� üũ�ϴ� ���.
	{
		// ��ǻ�� ������ ���� ȣ���ϴ� �Լ��� Ƚ���� �ٸ��� ������,
		// ���ڰ��� �����ϴ� �����δ� �ذ��ϴ°� ���� ���� �ʴ´�.
		// ��Ƽ�÷��� ������ �����غ���.
		// ���� ��� ��ǻ���� ���ɿ� �������, ������ �Լ� ȣ��(�Ǵ� �̵���)�� �����ؾ� �Ѵ�.
		newPos.x -= 100 * DeltaTime;
	}
	if (CKeyMgr::GetInstance()->GetKeyState(KEY::RIGHT) == KEY_STATE::KEY_HOLD) // ���ȴ��� üũ�ϴ� ���.
	{
		newPos.x += 100 * DeltaTime;
	}
	if (CKeyMgr::GetInstance()->GetKeyState(KEY::UP) == KEY_STATE::KEY_HOLD) // ���ȴ��� üũ�ϴ� ���.
	{
		newPos.y -= 100 * DeltaTime;
	}
	if (CKeyMgr::GetInstance()->GetKeyState(KEY::DOWN) == KEY_STATE::KEY_HOLD) // ���ȴ��� üũ�ϴ� ���.
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