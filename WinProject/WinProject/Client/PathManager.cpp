#include "pch.h"
#include "PathManager.h"
#include "CCore.h"

PathManager::PathManager():
	m_szContentPath{}, m_szRelativePath{}
{
}

PathManager::~PathManager()
{
}

void PathManager::Init()
{
	// ���� ���α׷��� ����� ��θ� �޾ƿ´�.
	GetCurrentDirectory(255, m_szContentPath);
	
	// ���������� ������ ��� ����
	/* ../bin\\contents\\ */
	size_t pathLength = wcslen(m_szContentPath);
	for (int i = pathLength - 1; i >= 0; i--)
	{
		// ����� \\�� ������ null ���ڸ� �־� �ش� ��α����� �����θ� �̴´�.
		if (m_szContentPath[i] == '\\')
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}
	wcscat_s(m_szContentPath, 255, L"\\bin\\contents\\"); 

	//SetWindowText(CCore::GetInstance()->GetMainHwnd(), m_szContentPath);
}

wstring PathManager::GetRelativePath(const wchar_t* _filePath)
{
	wstring strFilePath = _filePath;
	
	size_t pos = strFilePath.find(m_szContentPath);

	return strFilePath.substr(pos + wcslen(m_szContentPath));
}
