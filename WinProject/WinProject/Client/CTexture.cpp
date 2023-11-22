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
	// ���Ϸκ��� �ε��� �����͸� ��Ʈ������ ��ȯ
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(m_hBit);

	// ��Ʈ�ʰ� ������ DC
	m_dc = CreateCompatibleDC(CCore::GetInstance()->GetMainDC());

	// ��Ʈ�ʰ� DC ����
	HBITMAP hOldBIt = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hOldBIt);

	// ��Ʈ�� ���� ��ȯ
	GetObject(m_hBit, sizeof(BITMAP), &bitInfo);
}
