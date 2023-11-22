#pragma once
class PathManager
{
	SINGLE(PathManager);
private:
	wchar_t m_szContentPath[255];

public:
	void Init();
	const wchar_t* GetContentPath() { return m_szContentPath; }
};

