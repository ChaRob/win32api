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
	SINGLE(CCore);
private:
	// �����ڿ� �Ҹ��ڸ� ���´�.
	CCore();
	~CCore();
private:
	HWND m_hwnd;
	POINT m_ptResolution;

public:
	/*static CCore* GetInstance() {
		static CCore core;
		return &core;
	}*/
	int Init(HWND _hwnd, POINT _ptResolution);
	void Progress();
};

