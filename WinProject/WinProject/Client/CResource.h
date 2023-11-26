#pragma once

#include "global.h"
class CResource
{
public:
	CResource();
	virtual ~CResource();

private:
	wstring m_strKey;			// ���ҽ��� �ҷ��� �� ��Ī�� �� �ִ� �̸�
	wstring m_strRelativePath;	// ���ҽ� �����

public:
	void SetKey(wstring _key) { m_strKey = _key; }
	const wstring& GetKey() { return m_strKey; }
	void SetRelativePath(wstring _path) { m_strRelativePath = _path; }
	const wstring& GetRelativePath() { return m_strRelativePath; }


};

