#include "pch.h"
#include "ResourceMgr.h"

#include "PathManager.h"
#include "CResource.h"
#include "CTexture.h"

ResourceMgr::ResourceMgr() {}

ResourceMgr::~ResourceMgr()
{
    SafeDeleteMap(m_mapTexture);
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
    map<wstring, CResource*>::iterator iter = m_mapTexture.find(_strKey);
    if (iter == m_mapTexture.end()) {
        return nullptr;
    }
    return (CTexture*)iter->second;
}

CTexture* ResourceMgr::CreateTexture(const wstring& _strKey, UINT _width, UINT _height)
{
    CTexture* pTex = FindTexture(_strKey);
    if (pTex != nullptr) {
        return pTex;
    }

    pTex = new CTexture;
    pTex->Create(_width, _height);
    pTex->SetKey(_strKey);

    m_mapTexture.insert(make_pair(_strKey, pTex));

    return pTex;
}
