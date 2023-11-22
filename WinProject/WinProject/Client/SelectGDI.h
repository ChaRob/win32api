#pragma once
class SelectGDI
{
public:
	SelectGDI(HDC _dc, PEN_TYPE _pen);
	SelectGDI(HDC _dc, BRUSH_TYPE _brush);
	~SelectGDI();

private:
	HDC m_hDC;
	HPEN m_hDefalutPen;
	HBRUSH m_hDefalutBrush;

public:

};

