#pragma once

class CObject;

void CreateObject(CObject* _pObj, GROUP_TYPE _group);
void DeleteObejct(CObject* _pObj);
void ChangeScene(SCENE_TYPE _scene);

template<typename T>
void SafeDeleteVector(vector<T>& _vec) {
	for (int i = 0; i < _vec.size(); i++) {
		if (_vec[i] != nullptr) {
			delete _vec[i];
		}
	}
	_vec.clear();
}

template<typename T1, typename T2>
void SafeDeleteMap(map<T1, T2>& _map) {
	// template���� inner class ���� typename�� ����ؾ���.
	typename map<T1, T2>::iterator iter = _map.begin();
	for (; iter != _map.end(); iter++)
	{
		if (iter->second != nullptr) {
			delete iter->second;
		}
	}
	_map.clear();
}