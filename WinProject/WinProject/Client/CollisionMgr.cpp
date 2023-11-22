#include "pch.h"
#include "CollisionMgr.h"
#include "SceneMgr.h"
#include "CScene.h"

CollisionMgr::CollisionMgr():
	m_arrCheck{}
{

}

CollisionMgr::~CollisionMgr()
{

}

void CollisionMgr::Init()
{

}

void CollisionMgr::Update()
{
	for (UINT row = 0; row < (UINT)GROUP_TYPE::END; row++)
	{
		for (UINT col = row; col < (UINT)GROUP_TYPE::END; col++)
		{
			if (m_arrCheck[row] & (1 << col)) {
				CollisionUpdateGroup(row, col);
			}
		}
	}
}

void CollisionMgr::CheckGroup(GROUP_TYPE _group, GROUP_TYPE _target)
{
	// 더 작은 값의 그룹 타입을 행, 큰 값을 열(비트)로 사용한다.
	// 총 32개의 그룹을 지정할 수 있음.
	// 그룹별 관계는 삼각형으로 표기할 수 있다.
	/* ex)
		  3  2  1  0
		0 0  0  0  0
		1 1  0  0
		2 1  0
		3 0
	*/
	UINT left = (UINT)_group, right = (UINT)_target;
	if (left > right) {
		left = (UINT)_target;
		right = (UINT)_group;
	}

	// 만약 이미 값이 채워져있었다면 체크 해제하고, 아니라면 체크한다.
	if (m_arrCheck[left] & (1 << right)) {
		m_arrCheck[left] &= ~(1 << right);
	}
	else {
		m_arrCheck[left] |= (1 << right);
	}
}

void CollisionMgr::CollisionUpdateGroup(UINT _row, UINT _col)
{
	CScene* pCurScene = SceneMgr::GetInstance()->GetCurScene();

	// <주의!> 반환타입을 일치시켜야 함
	const vector<CObject*>& r = pCurScene->GetGroupObject((GROUP_TYPE)_row);
	const vector<CObject*>& c = pCurScene->GetGroupObject((GROUP_TYPE)_col);

	for (UINT i = 0; i < r.size(); i++)
	{
		if (r[i]->GetCollider() == nullptr)
			continue;

		for (UINT j = 0; j < c.size(); j++)
		{
			if (c[j]->GetCollider() == nullptr || r[i] == c[j])
				continue;

			if (IsCollisionOccur(r[i]->GetCollider(), c[j]->GetCollider())) {

			}
		}
	}
}

bool CollisionMgr::IsCollisionOccur(Collider* _pColLeft, Collider* _pColRight)
{
	
	return false;
}
