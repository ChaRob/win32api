#pragma once

/*
	ȭ�鿡 �����ϴ� ��� ��ü Ŭ����
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

