#pragma once

/*
	화면에 존재하는 모든 물체 클래스
*/
class CObject
{
private:
	Vector2 m_pos;
	Vector2 m_size;

public:
	CObject();
	~CObject();
	void SetPos(Vector2 _vPos) { m_pos = _vPos; }
	void SetScale(Vector2 _vScale) { m_size = _vScale; }
	Vector2 GetPos() { return m_pos; }
	Vector2 GetScale() { return m_size; }
};

