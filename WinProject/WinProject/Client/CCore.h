#pragma once
#include "pch.h"
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

	HBITMAP m_hBit;
	HDC m_memDC;

public:
	int Init(HWND _hwnd, POINT _ptResolution);
	void Progress();
	HWND GetMainHwnd() { return m_hwnd; }
	POINT GetResolution() { return m_ptResolution; }

private:
	void Update();
	void Render();
};

