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
	// �� ���� ���� �׷� Ÿ���� ��, ū ���� ��(��Ʈ)�� ����Ѵ�.
	// �� 32���� �׷��� ������ �� ����.
	// �׷캰 ����� �ﰢ������ ǥ���� �� �ִ�.
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

	// ���� �̹� ���� ä�����־��ٸ� üũ �����ϰ�, �ƴ϶�� üũ�Ѵ�.
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

	// <����!> ��ȯŸ���� ��ġ���Ѿ� ��
	const vector<CObject*>& r = pCurScene->GetGroupObject((GROUP_TYPE)_row);
	const vector<CObject*>& c = pCurScene->GetGroupObject((GROUP_TYPE)_col);

	// ID ���� ã�� ���� iterator
	map<ULONGLONG, bool>::iterator iter;

	for (UINT i = 0; i < r.size(); i++)
	{
		if (r[i]->GetCollider() == nullptr)
			continue;

		for (UINT j = 0; j < c.size(); j++)
		{
			if (c[j]->GetCollider() == nullptr || r[i] == c[j])
				continue;

			// �浹��!
			Collider* pRowCol = r[i]->GetCollider();
			Collider* pColCol = c[j]->GetCollider();

			// �� collider�� ID ������ ���� ����
			ColliderID ID;
			ID.leftID = pRowCol->GetID();
			ID.rightID = pColCol->GetID();

			iter = m_mapColInfo.find(ID.ID);
			if (iter == m_mapColInfo.end()) {
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}

			// �浹���� �ο� �� �̺�Ʈ �ο�
			if (IsCollisionOccur(pRowCol, pColCol)) {
				// ���� �浹 ��
				if (iter->second == true) {
					// �������� �浹�ߴ� ���� ���� => ��� �浹��

					if (r[i]->IsDead() || c[j]->IsDead()) {
						// �ٵ� �� �� �ϳ��� ������ ������Ʈ��� �浹 ����
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
					// �������� �浹���� �ʾ��� => ��� �浹 ��.
					if (!r[i]->IsDead() && !c[j]->IsDead()) {
						// �� �� ������ ������Ʈ�� �ƴ϶�� �۵�
						pRowCol->OnCollisionEnter(pColCol);
						pColCol->OnCollisionEnter(pRowCol);
						iter->second = true;
					}
				}
			}
			else {
				// ���� �浹���� ����
				if (iter->second == true) {
					// ������ �浹�ߴ� ���� ���� => ��� ������
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
