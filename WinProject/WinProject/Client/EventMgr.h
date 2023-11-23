#pragma once

struct tEvent {
	EVENT_TYPE	eEvent;
	DWORD_PTR	lParam;
	DWORD_PTR	wParam;
};

class EventMgr
{
	SINGLE(EventMgr);
private:
	vector<tEvent> m_vecEvent;
	vector<CObject*> m_vecDeadObj;

public:
	void Init();
	void Update();
	void AddEvent(const tEvent& _event) { m_vecEvent.push_back(_event); }

private:
	void Excute(const tEvent& _event);
};

