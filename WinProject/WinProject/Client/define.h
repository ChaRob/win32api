#pragma once

//
// ��ũ���Լ�, ��ó���⿡ ���� �Լ��� ȣ���ϴ� ����ó�� ���
// ���������� ġȯ�ϴ� �����̱� ������, ġȯ�� �� ��� �����ϴ��� �׻� ������ ��.
//

// �̱��� ��ũ���Լ�
#define SINGLE(type) public:\
							 static type* GetInstance()\
							 {\
								static type mgr;\
								return &mgr;\
							 }\
					private:\
							type();\
							~type();

// deltaTime ����ȭ
#define DeltaTime CTimeMgr::GetInstance()->GetDeltaTime()
#define DeltaTimef CTimeMgr::GetInstance()->GetDeltaTimef()