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