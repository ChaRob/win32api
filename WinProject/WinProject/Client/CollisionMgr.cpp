#include "pch.h"
#include "CollisionMgr.h"
#include "Collider.h"
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

	// ID 값을 찾기 위한 iterator
	map<ULONGLONG, bool>::iterator iter;

	for (UINT i = 0; i < r.size(); i++)
	{
		if (r[i]->GetCollider() == nullptr)
			continue;

		for (UINT j = 0; j < c.size(); j++)
		{
			if (c[j]->GetCollider() == nullptr || r[i] == c[j])
				continue;

			// 충돌함!
			Collider* pRowCol = r[i]->GetCollider();
			Collider* pColCol = c[j]->GetCollider();

			// 두 collider의 ID 데이터 조합 생성
			ColliderID ID;
			ID.leftID = pRowCol->GetID();
			ID.rightID = pColCol->GetID();

			iter = m_mapColInfo.find(ID.ID);
			if (iter == m_mapColInfo.end()) {
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}

			// 충돌판정 부여 및 이벤트 부여
			if (IsCollisionOccur(pRowCol, pColCol)) {
				// 현재 충돌 중
				if (iter->second == true) {
					// 이전에도 충돌했던 적이 있음 => 계속 충돌중

					if (r[i]->IsDead() || c[j]->IsDead()) {
						// 근데 둘 중 하나라도 삭제될 오브젝트라면 충돌 해제
						pRowCol->OnCollisionExit(pColCol);
						pColCol->OnCollisionExit(pRowCol);
						iter->second = false;
					}
					else {
						pRowCol->OnCollision(pColCol);
						pColCol->OnCollision(pRowCol);
					}
				}
				else {
					// 이전에는 충돌하지 않았음 => 방금 충돌 함.
					if (!r[i]->IsDead() && !c[j]->IsDead()) {
						// 둘 다 삭제될 오브젝트가 아니라면 작동
						pRowCol->OnCollisionEnter(pColCol);
						pColCol->OnCollisionEnter(pRowCol);
						iter->second = true;
					}
				}
			}
			else {
				// 현재 충돌하지 않음
				if (iter->second == true) {
					// 이전에 충돌했던 적이 있음 => 방금 떨어짐
					pRowCol->OnCollisionExit(pColCol);
					pColCol->OnCollisionExit(pRowCol);
				}
				iter->second = false;
			}
		}
	}
}

bool CollisionMgr::IsCollisionOccur(Collider* _pColLeft, Collider* _pColRight)
{
	Vector2 pLeftPos = _pColLeft->GetFinalPos();
	Vector2 pLeftSize = _pColLeft->GetSize();
	
	Vector2 pRightPos =  _pColRight->GetFinalPos();
	Vector2 pRightSize = _pColRight->GetSize();

	if (abs(pLeftPos.x - pRightPos.x) < (pLeftSize.x + pRightSize.x) / 2.f &&
		abs(pLeftPos.y - pRightPos.y) < (pLeftSize.y + pRightSize.y) / 2.f)
	{
		return true;
	}

	return false;
}
