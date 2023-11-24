#include "pch.h"
#include "PathManager.h"
#include "CCore.h"

PathManager::PathManager():
	m_szContentPath{}
{
}

PathManager::~PathManager()
{
}

void PathManager::Init()
{
	// 현재 프로그램이 실행된 경로를 받아온다.
	GetCurrentDirectory(255, m_szContentPath);
	
	// 상위폴더로 나가서 경로 지정
	/* ../bin\\contents\\ */
	size_t pathLength = wcslen(m_szContentPath);
	for (size_t i = pathLength - 1; i >= 0; i--)
	{
		// 경로중 \\를 만나면 null 문자를 넣어 해당 경로까지로 절대경로를 뽑는다.
		if (m_szContentPath[i] == '\\')
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}
	wcscat_s(m_szContentPath, 255, L"\\bin\\contents\\"); 

	//SetWindowText(CCore::GetInstance()->GetMainHwnd(), m_szContentPath);
}