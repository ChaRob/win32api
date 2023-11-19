#include "pch.h"
#include "CCore.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

CObject g_object;

CCore::CCore():
	m_hwnd(0),
	m_ptResolution{},
	m_hDC(0){}
CCore::~CCore()
{
	ReleaseDC(m_hwnd, m_hDC);
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

	g_object.SetPos(Vector2( m_ptResolution.x / 2, m_ptResolution.y / 2 ));
	g_object.SetScale(Vector2 {100, 100 });

	// Manager �ʱ�ȭ
	CKeyMgr::GetInstance()->Init();
	CTimeMgr::GetInstance()->Init();

	return S_OK;
}

void CCore::Progress()
{
	// Manager Update
	CTimeMgr::GetInstance()->Update();

	Update();
	Render();
}

void CCore::Update()
{
	// �񵿱� Ű ����� �Լ�
	// �����찡 Ȱ��ȭ�Ǿ� ���� �ʾƵ� �����ϱ� ������, �Ű�����.
	Vector2 newPos = g_object.GetPos();

	if (GetAsyncKeyState(VK_LEFT) & 0x8000) // ���ȴ��� üũ�ϴ� ���.
	{
		// ��ǻ�� ������ ���� ȣ���ϴ� �Լ��� Ƚ���� �ٸ��� ������,
		// ���ڰ��� �����ϴ� �����δ� �ذ��ϴ°� ���� ���� �ʴ´�.
		// ��Ƽ�÷��� ������ �����غ���.
		// ���� ��� ��ǻ���� ���ɿ� �������, ������ �Լ� ȣ��(�Ǵ� �̵���)�� �����ؾ� �Ѵ�.
		newPos.x -= 10 * DeltaTime;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) // ���ȴ��� üũ�ϴ� ���.
	{
		newPos.x += 10 * DeltaTime;
	}
	if (GetAsyncKeyState(VK_UP) & 0x8000) // ���ȴ��� üũ�ϴ� ���.
	{
		newPos.y -= 10 * DeltaTime;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) // ���ȴ��� üũ�ϴ� ���.
	{
		newPos.y += 10 * DeltaTime;
	}

	g_object.SetPos(newPos);
}

void CCore::Render()
{
	// �׸��� �۾�
	// ���� ȭ���̶�� ���� �ż������� ��� ��ȭ�ϴ� ����.
	// �� ����� �׸��� �����ְ�, �ڿ��� ���� �׸� ���� �ٽ� ��ü�ؼ� �����ְ�...�ݺ�

	Vector2 vPos = g_object.GetPos();
	Vector2 vScale = g_object.GetScale();

	Rectangle(m_hDC, 
		int(vPos.x - vScale.x / 2.f),
		int(vPos.y - vScale.y / 2.f),
		int(vPos.x + vScale.x / 2.f),
		int(vPos.y + vScale.y / 2.f));
}
