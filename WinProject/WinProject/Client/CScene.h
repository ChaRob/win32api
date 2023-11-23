#pragma once

// ���漱���� �Ͽ� �ش� Ŭ������ ������ ���
// object�ڵ尡 ����Ǿ �ִ��� ���� �����ϴ� ���� ����
class CObject;

class CScene
{
private:
	// ������Ʈ�� �׷찹����ŭ ������ ���͸� ����
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END];
	wstring				m_strName;
public:
	// ���Ϳ� �����͸� �߰��� �� �ִ� �Լ��� �ڽ� ��ҿ��� ����
	void AddObject(CObject* _tarObj, GROUP_TYPE _type)
	{
		m_arrObj[(UINT)_type].push_back(_tarObj);
	}

public:
	CScene();
	virtual ~CScene(); // �ڽ� �Ҹ��ڰ� ȣ��� �� �ֵ��� �����Լ��� ����
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }
	virtual void Enter() = 0; // �ش� Scene�� ���Խ� ȣ��
	virtual void Exit() = 0; // �ش� Scene�� Ż��� ȣ��

	// �� ���� �����ϴ� ������Ʈ�� ȣ��
	virtual void Update();
	virtual void FinalUpdate();
	virtual void Render(HDC _memDC);
	const vector<CObject*>& GetGroupObject(GROUP_TYPE _type) { return m_arrObj[(UINT)_type]; }
	void DeleteGroup(GROUP_TYPE _group);
	void DeleteGroupAll();
};

