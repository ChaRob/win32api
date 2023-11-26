#pragma once

#include "global.h"
class CResource
{
public:
	CResource();
	virtual ~CResource();

private:
	wstring m_strKey;			// 리소스를 불러올 때 지칭할 수 있는 이름
	wstring m_strRelativePath;	// 리소스 상대경로

public:
	void SetKey(wstring _key) { m_strKey = _key; }
	const wstring& GetKey() { return m_strKey; }
	void SetRelativePath(wstring _path) { m_strRelativePath = _path; }
	const wstring& GetRelativePath() { return m_strRelativePath; }


};

