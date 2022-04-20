//#pragma once


#include "ofApp.h"
//#include "GameObject.h"

class GameObjectList: public GameObject {
public:
	GameObjectList* next;
	GameObjectList* before;
	bool caught; 

	GameObjectList() {
		caught = false; 
	
	};

	~GameObjectList() {
	};

	void del()
	{}; 
};
