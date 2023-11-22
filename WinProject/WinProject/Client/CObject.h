#pragma once

class Collider;

/*
	ȭ�鿡 �����ϴ� ��� ��ü Ŭ����
*/
class CObject
{
private:
	Vector2 m_pos;
	Vector2 m_size;

	Collider* m_pCollider;

public:
	CObject();
	virtual ~CObject(); // �ڽ� �Ҹ��ڰ� ȣ��� �� �ֵ��� �����Լ��� ����
	virtual void Update() = 0;
	virtual void FinalUpdate() final;
	virtual void Render(HDC _memDC);

public:
	void SetPos(Vector2 _vPos) { m_pos = _vPos; }
	void SetScale(Vector2 _vScale) { m_size = _vScale; }
	Vector2 GetPos() { return m_pos; }
	Vector2 GetScale() { return m_size; }
	void CreateCollider();
	void ComponentRender(HDC _memDC);
	Collider* GetCollider() { return m_pCollider; }
};