#pragma once
#include "CObject.h"

class CTexture;

class Tile :
    public CObject
{
public:
    Tile();
    ~Tile();

private:
    CTexture* m_pTileTex;
    int m_idx;              // 출력하고싶은 타일 번호

private:
    virtual void Render(HDC _dc);
    virtual void Update();
    Tile* Clone() { return new Tile(*this); }

public:
    void SetTexture(CTexture* _pTex) { m_pTileTex = _pTex; }
};

