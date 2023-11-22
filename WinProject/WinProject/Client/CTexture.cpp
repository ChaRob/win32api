#include "pch.h"
#include "CTexture.h"

CTexture::CTexture() :
	m_dc(0), m_hBit(0), bitInfo{}
{
}

CTexture::~CTexture()
{
	DeleteDC(m_dc);
	DeleteObject(m_hBit);
}

void CTexture::Load(const wstring& _strFilePath)
{
	// 파일로부터 로딩한 데이터를 비트맵으로 변환
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(m_hBit);

	// 비트맵과 연결할 DC
	m_dc = CreateCompatibleDC(CCore::GetInstance()->GetMainDC());

	// 비트맵과 DC 연결
	HBITMAP hOldBIt = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hOldBIt);

	// 비트맵 정보 반환
	GetObject(m_hBit, sizeof(BITMAP), &bitInfo);
}
