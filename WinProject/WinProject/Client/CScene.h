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
	void Update();
	void FinalUpdate();
	void Render(HDC _memDC);
};

