#pragma once

//
// 매크로함수, 전처리기에 의해 함수를 호출하는 형식처럼 사용
// 주의할점은 치환하는 형식이기 때문에, 치환될 때 어떻게 동작하는지 항상 유의할 것.
//

// 싱글톤 매크로함수
#define SINGLE(type) public:\
							 static type* GetInstance()\
							 {\
								static type mgr;\
								return &mgr;\
							 }