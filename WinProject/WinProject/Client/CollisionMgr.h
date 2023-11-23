#pragma once

union ColliderID {
	struct {
		UINT leftID;
		UINT rightID;
	};
	ULONGLONG ID;
};

class CollisionMgr
{
	SINGLE(CollisionMgr);

private:
	// �׷찣�� �浹üũ ��Ʈ����
	UINT m_arrCheck[(UINT)GROUP_TYPE::END];
	// Collider���� ���� ������ �浹 ����
	map<ULONGLONG, bool> m_mapColInfo;

public:
	void Init();
	void Update();
	void CheckGroup(GROUP_TYPE _group, GROUP_TYPE _target);
	void DeleteGroup() { memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); }

private:
	void CollisionUpdateGroup(UINT _row, UINT _col);
	bool IsCollisionOccur(Collider* _pColLeft, Collider* _pColRight);
};

