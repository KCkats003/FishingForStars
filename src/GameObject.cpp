#include "ofApp.h"

void GameObject::move(int Xmov, int Ymov) {

	if ((posX + Xmov) < 700) {
		posX = posX + Xmov;
	}
	else 
	{
		posX = 500;
	}
	
	if ((posY + Xmov) > 700) {
		posY = 699;
	}
	else if ((posY + Xmov) < 10) {
		posY = 11;
	}
	else {
		
		posY = posY + Ymov;
	}
	
};


void GameObject::setLevel(int newLevel) {

	if (newLevel > 0 || newLevel < 4) {
		level = newLevel;
	
	}
};


void GameObject::update() {

	box.set(posX, posY, img->getWidth(), img->getHeight());
};


bool GameObject::collision(ofRectangle otherRect) {
	bool intersect; 
	intersect = false; 
	//box.getIntersection()
	intersect = box.intersects(otherRect);

	/*intersect = true;
	if (box.getIntersection(otherRect) <  0) {
	
		intersect = false;
	}*/
	
	//intersect = true;
	return intersect; 
};