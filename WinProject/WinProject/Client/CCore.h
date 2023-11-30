#pragma once
#include "pch.h"
#include "CTexture.h"
/*
	싱글톤 패턴
	객체의 생성을 1개로 제한함
*/

//class CCore
//{
//private:
//	// 생성자와 소멸자를 막는다.
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
	// 싱글톤 객체로 지정
	// 생성자와 소멸자까지 막는다.
	SINGLE(CCore);
private:
	HWND m_hwnd;			// 메인 윈도우 핸들
	POINT m_ptResolution;	// 메인 윈도우 해상도
	HDC m_hDC;				// 메인 윈도우에 Draw 할 DC

	//HBITMAP m_hBit;
	//HDC m_memDC;
	CTexture* m_pMemTex;	// 백버퍼 텍스쳐

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

