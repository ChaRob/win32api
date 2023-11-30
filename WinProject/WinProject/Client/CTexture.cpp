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

void CTexture::Create(UINT _width, UINT _height)
{
	HDC mainDC = CCore::GetInstance()->GetMainDC();

	m_hBit = CreateCompatibleBitmap(mainDC, _width, _height);
	m_dc = CreateCompatibleDC(mainDC);

	// m_memDC가 기존에 가리키고 있던 bitmap은 사용하지 않으므로 제거한다.
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hOldBit);

	// 비트맵 정보 반환
	GetObject(m_hBit, sizeof(BITMAP), &bitInfo);
}
