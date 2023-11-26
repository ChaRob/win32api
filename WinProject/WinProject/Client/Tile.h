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
    int m_idx;              // ����ϰ���� Ÿ�� ��ȣ

private:
    virtual void Render(HDC _dc);
    virtual void Update();
    Tile* Clone() { return new Tile(*this); }

public:
    void SetTexture(CTexture* _pTex) { m_pTileTex = _pTex; }
};

