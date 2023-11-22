#pragma once
class CollisionMgr
{
	SINGLE(CollisionMgr);

private:
	// 그룹간의 충돌체크 매트릭스
	UINT m_arrCheck[(UINT)GROUP_TYPE::END];
	// Collider간의 이전 프레임 충돌 정보
	

public:
	void Init();
	void Update();
	void CheckGroup(GROUP_TYPE _group, GROUP_TYPE _target);
	void DeleteGroup() { memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); }

private:
	void CollisionUpdateGroup(UINT _row, UINT _col);
	bool IsCollisionOccur(Collider* _pColLeft, Collider* _pColRight);
};

