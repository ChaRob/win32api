#pragma once
#include "CResource.h"
class CTexture :
    public CResource
{
private:
    CTexture();
    ~CTexture();
    friend class ResourceMgr;

private:
    HDC m_dc;
    HBITMAP m_hBit;
    BITMAP bitInfo;

public:
    void Load(const wstring& _strFilePath);
    UINT GetBitmapWidth() { return bitInfo.bmWidth; }
    UINT GetBitmapHeight() { return bitInfo.bmHeight; }
    const HDC& GetDC() { return m_dc; }
};

