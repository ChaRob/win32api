#pragma once
#include "pch.h"
#include "CTexture.h"
/*
	�̱��� ����
	��ü�� ������ 1���� ������
*/

//class CCore
//{
//private:
//	// �����ڿ� �Ҹ��ڸ� ���´�.
//	CCore();
//	~CCore();
//	static CCore* instance;
//public:
//	static CCore* GetInstance() {
//		if (instance == nullptr) {
//			instance = new CCore();
//		}
//		return instance;
//	}
//
//	static void ReleaseInstance() {
//		if (instance != nullptr) {
//			delete instance;
//			instance = nullptr;
//		}
//	}
//};
class CCore
{
	// �̱��� ��ü�� ����
	// �����ڿ� �Ҹ��ڱ��� ���´�.
	SINGLE(CCore);
private:
	HWND m_hwnd;			// ���� ������ �ڵ�
	POINT m_ptResolution;	// ���� ������ �ػ�
	HDC m_hDC;				// ���� �����쿡 Draw �� DC

	//HBITMAP m_hBit;
	//HDC m_memDC;
	CTexture* m_pMemTex;	// ����� �ؽ���

	HBRUSH m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN m_arrPen[(UINT)PEN_TYPE::END];

private:
	void Update();
	void Render();
	void CreateBrushPen();

public:
	int Init(HWND _hwnd, POINT _ptResolution);
	void Progress();
	HWND GetMainHwnd() { return m_hwnd; }
	POINT GetResolution() { return m_ptResolution; }
	HDC GetMainDC() { return m_hDC; }
	const HBRUSH& GetBrush(BRUSH_TYPE _brush) { return m_arrBrush[(UINT)_brush]; }
	const HPEN& GetPen(PEN_TYPE _pen) { return m_arrPen[(UINT)_pen]; }
};

