#include "pch.h"
#include "CCore.h"

CCore::CCore(){}
CCore::~CCore(){}

int CCore::Init(HWND _hwnd, POINT _ptResolution)
{
	m_hwnd = _hwnd;
	m_ptResolution = _ptResolution;

	// �ػ󵵿� �°� ������ ũ�� ����


	return S_OK;
}

void CCore::Progress()
{

}
