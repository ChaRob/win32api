#pragma once
#include "pch.h"
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
	SINGLE(CCore);
private:
	// 생성자와 소멸자를 막는다.
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

