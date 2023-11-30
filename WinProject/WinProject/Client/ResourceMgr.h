#pragma once

#include "global.h"
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
	CTexture* CreateTexture(const wstring& _strKey, UINT _width, UINT _height);
};

