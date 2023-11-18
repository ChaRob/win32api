#include "pch.h"
#include "CCore.h"

CCore::CCore(){}
CCore::~CCore(){}

int CCore::Init(HWND _hwnd, POINT _ptResolution)
{
	m_hwnd = _hwnd;
	m_ptResolution = _ptResolution;

	// 해상도에 맞게 윈도우 크기 조절


	return S_OK;
}

void CCore::Progress()
{

}
