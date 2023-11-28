#pragma once
#include "global.h"

// 전방선언을 하여 해당 클래스가 있음을 명시
// object코드가 변경되어도 최대한 서로 참조하는 것을 방지
class CObject;

class CScene
{
private:
	// 오브젝트의 그룹갯수만큼 관리할 벡터를 선언
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END];
	wstring				m_strName;

	// 타일의 가로, 세로 갯수
	UINT				m_tileX;
	UINT				m_tileY;

public:
	CScene();
	virtual ~CScene(); // 자식 소멸자가 호출될 수 있도록 가상함수로 구현
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }
	virtual void Enter() = 0; // 해당 Scene에 진입시 호출
	virtual void Exit() = 0; // 해당 Scene에 탈출시 호출

	// 각 씬에 존재하는 오브젝트들 호출
	virtual void Update();
	virtual void FinalUpdate();
	virtual void Render(HDC _memDC);

public:
	// 벡터에 데이터를 추가할 수 있는 함수를 자식 요소에게 제공
	void AddObject(CObject* _tarObj, GROUP_TYPE _type)
	{
		m_arrObj[(UINT)_type].push_back(_tarObj);
	}
	const vector<CObject*>& GetGroupObject(GROUP_TYPE _type) { return m_arrObj[(UINT)_type]; }
	CObject* const DeleteObjectInGroup(GROUP_TYPE _type, CObject* const _target);
	void DeleteGroup(GROUP_TYPE _group);
	void DeleteGroupAll();
	void CreateTile(UINT _xCount, UINT _yCount);
	const UINT& GetTileX() { return m_tileX; }
	const UINT& GetTileY() { return m_tileY; }
};

