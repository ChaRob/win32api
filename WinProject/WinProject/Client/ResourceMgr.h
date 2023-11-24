#pragma once

class CResource;
class CTexture;

class ResourceMgr
{
	SINGLE(ResourceMgr);
private:
	map<wstring, CResource*> m_mapTexture;

public:
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);
	CTexture* FindTexture(const wstring& _strKey);
};

