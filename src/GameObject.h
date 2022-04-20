//#pragma once
#include "ofApp.h"
class GameObject {
public: 
	GameObject() {
	
		posX = 0; 
		posY = 50; 
		speed = 1; 
		level = 2; 
		
		caught = false; 
	}; 

	~GameObject() {}; 

	bool caught; 

	int posX; 
	int posY; 
	int speed; 
	int level;  // this should be 1, 2, 3, 3 is the furthest away from cam, 1 is the closest to cam 
	ofImage * img; 

	void move(int Xmov, int Ymov); 
	ofRectangle  box;

	bool collision(ofRectangle otherRect);

	void setLevel(int newLevel); 
	void update(); 
};