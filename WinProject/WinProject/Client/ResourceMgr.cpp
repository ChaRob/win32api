#include "pch.h"
#include "ResourceMgr.h"

#include "PathManager.h"
#include "CTexture.h"

ResourceMgr::ResourceMgr() {}

ResourceMgr::~ResourceMgr()
{
    map<wstring, CTexture*>::iterator iter = m_mapTexture.begin();
    for (; iter != m_mapTexture.end(); iter++)
    {
        delete iter->second;
    }
}

CTexture* ResourceMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
    CTexture* pTex = FindTexture(_strKey);
    if (pTex != nullptr) {
        return pTex;
    }

    wstring strFilePath = PathManager::GetInstance()->GetContentPath() + _strRelativePath;
    
    pTex = new CTexture;
    pTex->Load(strFilePath);

    pTex->SetKey(_strKey);
    pTex->SetRelativePath(_strRelativePath);

    m_mapTexture.insert(make_pair(_strKey, pTex));

    return pTex;
}

CTexture* ResourceMgr::FindTexture(const wstring& _strKey)
{
    map<wstring, CTexture*>::iterator iter = m_mapTexture.find(_strKey);
    if (iter == m_mapTexture.end()) {
        return nullptr;
    }
    return iter->second;
}
