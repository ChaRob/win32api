#include "pch.h"
#include "Tile.h"
#include "Camera.h"
#include "CTexture.h"

Tile::Tile():
	m_pTileTex(nullptr), m_idx(0)
{
	SetScale(Vector2(TILE_SIZE, TILE_SIZE));
}

Tile::~Tile()
{
}

void Tile::Render(HDC _dc)
{
	if (m_pTileTex == nullptr || m_idx <= -1) return;

	UINT width = m_pTileTex->GetBitmapWidth();
	UINT height = m_pTileTex->GetBitmapHeight();

	UINT maxCol = width / TILE_SIZE;
	UINT maxRow = height / TILE_SIZE;

	UINT curRow = m_idx / maxCol;
	UINT curCol = m_idx % maxCol;

	// 만약 이미지 범위를 벗어난 인덱스라면 경고 발생
	if (curRow >= maxRow) assert(nullptr);

	Vector2 renderPos = Camera::GetInstance()->GetRenderPos(GetPos());
	Vector2 scale = GetScale();

	BitBlt(_dc,
		(int)renderPos.x,
		(int)renderPos.y,
		(int)scale.x,
		(int)scale.y,
		m_pTileTex->GetDC(),
		curCol * TILE_SIZE,
		curRow * TILE_SIZE,
		SRCCOPY);

	/*Rectangle(_dc,
		(int)renderPos.x, (int)renderPos.y,
		(int)(renderPos.x + scale.x), (int)(renderPos.y + scale.y));*/
}

void Tile::Update()
{

}
