#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	
	ofSetWindowShape(1500, 1000);
	
	
	m_font.load("franklinGothic.otf", 16);

	m_arduino.connect("COM4", 57600);
	//m_arduino.connect(config::ARDUINO_DEVICE_NAME, 57600);

	m_input_valy = 0.0f;
	m_input_valx = 0.0f;
	m_accel_valx = 0.0f;
	m_accel_valy = 0.0f;
	m_accel_valz = 0.0f;
	m_button_val = 0.0f;
	yDegreeTilt = 0.0f;
	xDegreeTilt = 0.0f;
	mapButtonPress= false;
	mapVisibilty= true;
	ofAddListener(m_arduino.EInitialized, this, &ofApp::setupArduino);
	//end

	m_bSetup = false;
	bg.load("BGSHORT.png");

	//loading in the kites 
	kite1.load("kite1.png");
	kite2.load("kite2.png");
	kite3.load("kite3.png");
	m_miniMap1.load("minimap1.png");
	m_miniMap2.load("minimap2.png");
	m_miniMap3.load("minimap3.png");

	//loading in Cliff 1 
	cliff1.load("Cliff1_1.png");
	Cliff1_1.img = &cliff1;
	Cliff1_1.posX = 200;
	Cliff1_1.posY = 800;
	Cliff1_1.level = 1;


	//loading in Cliff 1 
	cliff1.load("Cliff1_2.png");
	Cliff1_2.img = &cliff1;
	Cliff1_2.posX = 800;
	Cliff1_2.posY = 800;
	Cliff1_2.level = 1;


	//loading in Cliff 1 
	cliff1.load("Cliff1_3.png");
	Cliff1_3.img = &cliff1;
	Cliff1_3.posX = 1000;
	Cliff1_3.posY = 800;
	Cliff1_3.level = 1;

	//loading in Cliff 2 
	cliff2.load("Cliff2_2.png");
	Cliff2_1.img = &cliff2;
	Cliff2_1.posX = 600;
	Cliff2_1.posY = 400;
	Cliff2_1.level = 2;

	//loading in Cliff 3 
	cliff3.load("Cliff3_3.png");
	Cliff3_1.img = &cliff3;
	Cliff3_1.posX = 800;
	Cliff3_1.posY = 200;
	Cliff3_1.level = 3;


	bgMov = 0; 

	currentMode = layer2;

	currentZoom = 0; 
	cam.setDistance(0);


	player.img = &kite2;
	player.posX = 400;
	player.posY = 400;

	currentSpeed = 1;


	bgImg.img = &bg;
	bgImg.posX = 0;
	bgImg.posY = 0;

	bgImg2.img = &bg;
	bgImg2.posX = 3579;
	bgImg2.posY = 0;



	//intialize the stars 
	StarsCollected = 0; 
	m_Star1.load("Star1.png");
	m_Star2.load("Star2.png");
	m_Star3.load("Star3.png");
	
	Star1.img = &m_Star1;
	Star1.level = 1;
	Star1.posY = 200; 

	Star2.img = &m_Star2;
	Star2.level = 2; 
	Star1.posY = 400;

	Star3.img = &m_Star3;
	Star3.level = 3;
	Star1.posY = 800;


	pixelFont.load("PixelFJVerdana12pt.ttf", 19);

	currentWinState = play; 

	hitSound.load("hitSound.wav");
	starSound.load("starSound.wav");
	winSound.load("winSound.wav");

	backgroundSound.load("backgroundSound.mp3");
	backgroundSound.play();

	mute = false; 

}

//--------------------------------------------------------------
void ofApp::update(){
	
	updateArduino();

	//these are some pointers for resetting when things go off screen 
	float* p_layerMov;
	GameObject* curr_Object;
	GameObjectList* curr_Star;

	if (bgImg.posX >= -3579) {
		bgImg.posX = bgImg.posX - (10 * currentSpeed);

	}
	else
	{
		bgImg.posX = 0;
	}

	if (bgImg2.posX >= 0) {
		bgImg2.posX = bgImg2.posX - (10 * currentSpeed);

	}
	else
	{
		bgImg2.posX = bgImg.posX + 3579;
	}



	//how much to move level 3 (furthest to cam)
	layer3Mov = layer3Mov - (1 * currentSpeed);

	p_layerMov = &layer3Mov;
	curr_Object = &Cliff3_1;

	Cliff3_1.level = 3; 
	reset(p_layerMov, curr_Object); //updates and resets the numbers so they repeat 

	curr_Star = &Star1;
	resetStars(p_layerMov, curr_Star);



	//how much to move level 2 
	layer2Mov = layer2Mov - (1.5 * currentSpeed);

	p_layerMov = &layer2Mov;
	curr_Object = &Cliff2_1;

	curr_Star = &Star2;
	reset(p_layerMov, curr_Object);
	resetStars(p_layerMov, curr_Star);


	//how much to move level 1 (closest to cam)
	layer1Mov = layer1Mov - (2 * currentSpeed);

	p_layerMov = &layer1Mov;

	curr_Object = &Cliff1_1;
	reset(p_layerMov, curr_Object);

	curr_Object = &Cliff1_2;
	reset(p_layerMov, curr_Object);

	curr_Object = &Cliff1_3;
	reset(p_layerMov, curr_Object);

	curr_Star= &Star2;
	resetStars(p_layerMov, curr_Star);



	//need to update the collision boxes on these objects
	player.update(); 
	
	Cliff1_1.update();
	Cliff2_1.update();
	Cliff3_1.update();

	Star1.update();
	Star2.update();
	Star3.update();

	//check if the player has won or not 
	if (StarsCollected > 9) {
		currentWinState = won; 
		if (mute == false) {
			winSound.play();
		}
	}



}


//for reseting images and cliffs 
void ofApp::reset(float* num, GameObject* Object) {
	float addnum = *num;
	int level = Object->level;
	if (*num >= -2100) {
		Object->posX = 2010 + addnum;
	}

	if (*num < -2100) {
		*num = 0;
		Object->posX = 2010 + addnum + Object->posX;
		

		Object->caught = false;

		switch (level) {
		case  3:
			Object->posY = 200;
			break;
		case 2:
			Object->posY = 400;
			break; 
		case 1:
			Object->posY = 800;
			break; 
		}

	}

};


//for reseting stars  
void ofApp::resetStars(float* num, GameObjectList* Object) {

	float addnum = *num;
	int level = Object->level;
	if (*num >= -2100 && Object->caught == false) {
	
		Object->posX = 2010 + addnum;

	}

	if (*num < -2100) {
		*num = 0;
		Object->caught = false;
		Object->posX = 2010 + addnum;

		Object->posY = 400;

		switch (level) {
		case  3:
			Object->posY = 100;
			break; 
		case 2:
			Object->posY = 400;
			break; 
		case 1:
			Object->posY = 800;
			break; 

		}


	}

};


//--------------------------------------------------------------
void ofApp::draw(){
	//cam.begin();

	//default color 
	ofSetColor(255, 255, 255);


	/*drawing only the background, this cannot be interacted with */

	bgImg.img->draw(bgImg.posX, bgImg.posY);
	bgImg2.img->draw(bgImg2.posX, bgImg2.posY);


	//-------------------------DRAWING LAYER 3 ---------------------------------------
	ofPushMatrix();
	ofScale(0.7, 0.7, 0.7);
	ofSetColor(106, 245, 253);

	//drawing things from level 3 (furthest away from the cam)
	Cliff3_1.img->draw(Cliff3_1.posX, Cliff3_1.posY);
	Star3.img->draw(Star3.posX, Star3.posY);

	//collecting stars on level 3
	if (player.collision(Star3.box) == true && Star3.caught == false) {
		StarsCollected = StarsCollected + 1;
		Star3.caught = true;
		Star3.posY = 3000;

		if (mute == false) {
			starSound.play();
		}


	}

	if (player.collision(Cliff3_1.box) && Cliff3_1.caught == false) {
		StarsCollected = StarsCollected - 1;
		Cliff3_1.caught = true; 

		if (mute == false) {
			hitSound.play();
		}

	}

	//drawing the kite for level 3 
	if (currentMode == layer3) {
		player.img = &kite3;
		player.img->draw(player.posX, player.posY);
	}

	ofPopMatrix();

	//-------------------------DRAWING LAYER 2 (default layer)---------------------------------------
	ofPushMatrix();
	ofSetColor(255, 255, 255);
	ofScale(0.9, 0.9, 0.9);
	//drawing things from level 2 (middle)
	Cliff2_1.img->draw(Cliff2_1.posX, Cliff2_1.posY);
	Star2.img->draw(Star2.posX, Star2.posY);


	//collecting stars on level 2 
	if (player.collision(Star2.box) == true && Star2.caught == false) {
		StarsCollected = StarsCollected + 1;
		Star2.caught = true;
		Star2.posY = 3000;

		if (mute == false) {
			starSound.play();
		}


	}
	//collisions with cliff in layer 2 
	if (player.collision(Cliff2_1.box) && Cliff2_1.caught == false) {
		StarsCollected = StarsCollected - 1;
		Cliff2_1.caught = true;
		if (mute == false) {
			hitSound.play();
		}

	}


	//DRAW the KITE on layer 2 
	if (currentMode == layer2) {

		player.img = &kite2;
		cout << player.posY << endl;
		player.img->draw(player.posX, player.posY);

		cout << "Player X: " << player.posX << endl;
		cout << "Player Y: " << player.posY << endl;
	}

	ofPopMatrix();





	//-------------------------DRAWING LAYER 1 ---------------------------------------
	//drawing things from level 1 (closest)
	ofPushMatrix();
	ofSetColor(180, 140, 100);
	
	Star1.img->draw(Star1.posX, Star1.posY);
	Cliff1_1.img->draw(Cliff1_1.posX, Cliff1_1.posY);
	

	//drawing the kite on level 1 
	if (currentMode == layer1) {
		player.img = &kite1;
		player.img->draw(player.posX, player.posY);
	}

	//collecting stars on level 1
	if (player.collision(Star1.box) == true && Star1.caught == false) {
		StarsCollected = StarsCollected + 1;
		Star1.caught = true;
		Star1.posY = 3000;

		if (mute == false) {
			starSound.play();
		}

	}

	//hitting cliffs on level 1 
	if (player.collision(Cliff1_1.box) && Cliff1_1.caught == false) {
		StarsCollected = StarsCollected - 1;
		Cliff1_1.caught = true;

		if (mute == false) {
			hitSound.play();
		}

	}

	ofPopMatrix();


	//-------------------------DRAWING UI LAYER ---------------------------------------

	
	ofPushMatrix();
	ofSetColor(0, 0, 0);

	pixelFont.drawString("Stars Collected #: ", 900, 100);
	pixelFont.drawString(ofToString(StarsCollected), 1400, 100);

	if (mute == true) {
		pixelFont.drawString("Muted", 1400, 100);
	}

	if (currentWinState == won) {
		pixelFont.drawString("You won!", 1000, 500);
	}
	ofPopMatrix();



	if (yDegreeTilt == -1) {
		currentMode = layer1;
	}
	else if (yDegreeTilt == 0) {
		currentMode = layer2;
	}
	else {
		currentMode = layer3;
	}

	if (xDegreeTilt == 1) {
		player.move(0, -1);
	}
	else if (xDegreeTilt == -1) {
		player.move(0, 1);
	}

	ofSetColor(255, 255, 255);

	if (mapVisibilty) {
		if (currentMode == layer1) {
			m_miniMap1.draw(1200, 550, 200, 220);
		}
		else if (currentMode == layer2) {
			m_miniMap2.draw(1200, 550, 200, 220);
		}
		else {
			m_miniMap3.draw(1200, 550, 200, 220);
	
	}
}


	
}

//--------------------------------------------------------------
void ofApp::zoom(int zoomFactor) {
	cam.setDistance(zoomFactor);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == ' '){
		currentZoom = currentZoom + 10; 
		cam.setDistance(currentZoom);

}
	if (key == 'A') {
		currentZoom = currentZoom - 10;
		cam.setDistance(currentZoom);
	
	}
	if (key == 'w') {
		player.move(0, -10);
		
	
	}
	if (key == 's') {
		player.move(0, 10);
		
	}
	
	if (key == 'z') {
		currentMode = layer1;
		
	}

	if (key == 'x') {
		currentMode = layer2;
		
	}
	if (key == 'c') {
		currentMode = layer3;
		
	}
	if (key == 'v') {
		mapVisibilty = !mapVisibilty;
	}

	if (key == 'f') {
		speed(0.1);
		
	}

	if (key == 'g') {
		speed(-0.1);
	
	}

	if (key == 'm') {
		if (mute == false) {
			mute = true; 
		}

		if (mute == true) {
			mute = false; 
		}
	}



}


void ofApp::speed(float speedChange) {


	currentSpeed = currentSpeed + speedChange;
	if (currentSpeed < 0.1) {
		currentSpeed = 0.1;
	}

	if (currentSpeed > 10) {
		currentSpeed = 10;
	}

};


//--------------------------------------------------------------
void ofApp::setupArduino(const int & _version)
{
	/**
	 Look under examples/communication/firmata for more examples ..
	 **/

	m_bSetup = true;

	// remove listener because we don't need it anymore
	ofRemoveListener(m_arduino.EInitialized, this, &ofApp::setupArduino);

	// print firmware name and version to the console
	ofLogNotice() << m_arduino.getFirmwareName();
	ofLogNotice() << "firmata v" << m_arduino.getMajorFirmwareVersion() << "." << m_arduino.getMinorFirmwareVersion();

	//analog input
	m_arduino.sendAnalogPinReporting(PIN_ANALOG_INPUTX, ARD_ANALOG);
	m_arduino.sendAnalogPinReporting(PIN_ANALOG_INPUTY, ARD_ANALOG);
	m_arduino.sendAnalogPinReporting(PIN_ANALOG_ACCEL_X, ARD_ANALOG);
	m_arduino.sendAnalogPinReporting(PIN_ANALOG_ACCEL_Y, ARD_ANALOG);
	m_arduino.sendAnalogPinReporting(PIN_ANALOG_ACCEL_Z, ARD_ANALOG);
	m_arduino.sendDigitalPinMode(PIN_DIGITAL_INPUT, ARD_INPUT); 
	//m_arduino.sendDigitalPinMode(PIN_AUDIO_TOGGLE, ARD_INPUT);

	if (m_arduino.getDigital(PIN_DIGITAL_INPUT)) {
		// do something on high
		m_button_val = m_arduino.getDigital(PIN_DIGITAL_INPUT);
		std::cout << "digital pin: " + m_button_val << std::endl;
	}
	else {
		// do something on low
		m_button_val = m_arduino.getDigital(PIN_DIGITAL_INPUT);
		std::cout << "digital pin: " + m_button_val << std::endl;
	}

	//PMW/digital output
	m_arduino.sendDigitalPinMode(PIN_PWM_OUTPUT, ARD_PWM);

	ofAddListener(m_arduino.EDigitalPinChanged, this, &ofApp::digitalPinChanged);

	ofAddListener(m_arduino.EAnalogPinChanged, this, &ofApp::analogPinChanged);
}

//--------------------------------------------------------------
void ofApp::updateArduino() {

	// update the arduino, get any data or messages.
	// the call to m_arduino.update() is required
	m_arduino.update();
	cout << "Update" << endl;
}

void ofApp::digitalPinChanged(const int & pinNum) {
	//std::cout  << "digital pin: " + ofToString(pinNum) + " : " + ofToString(m_arduino.getDigital(pinNum)) << std::endl;
	if (pinNum == PIN_DIGITAL_INPUT) {
		//get analog value
		m_button_val = m_arduino.getDigital(pinNum);
		std::cout << "digital pin: " + m_button_val << std::endl;
		//m_button_val = (int)ofMap(m_button_val, 0, 1023, 0, 255);

		if (m_button_val) {
			if (mapButtonPress) {
				mapVisibilty = !mapVisibilty;
				mapButtonPress = false;
			}
		}
		else {
			mapButtonPress = true; 
		}
		//send out pmw value
	}

	if (pinNum == PIN_AUDIO_TOGGLE) {

		//get analog value
		m_audio_toggle_val = m_arduino.getDigital(pinNum);
		std::cout << "digital pin: " + m_audio_toggle_val << std::endl;
		//m_button_val = (int)ofMap(m_button_val, 0, 1023, 0, 255);

		if (m_audio_toggle_val) {
			if (audioButtonPress) {
				mute = !mute;
				mapButtonPress = false;
			}

		}
		else {
			audioButtonPress = true;
		}

		//send out pmw value

	}
}

void ofApp::analogPinChanged(const int & pinNum) {
	//std::cout  << "analog pin: " + ofToString(pinNum) + " : " + ofToString(m_arduino.getAnalog(pinNum)) << std::endl;
	if (pinNum == PIN_ANALOG_INPUTY) {

		//get analog value
		m_input_valy = m_arduino.getAnalog(pinNum);
		m_input_valy = (int)ofMap(m_input_valy, 0, 1023, 0, 100);
		if (m_input_valy > 80) {
				speed(0.1);
			std::cout << "speed" << std::endl;
		}
		else if ( 20 < m_input_valy) {

			std::cout << "no change speed" << std::endl;
		}
		else  {
				speed(-0.1);
			std::cout << "slow" << std::endl;
		}
	}

	if (pinNum == PIN_ANALOG_INPUTX) {

		//get analog value
		m_input_valx = m_arduino.getAnalog(pinNum);
		m_input_valx = (int)ofMap(m_input_valx, 0, 1023, -512, 512);

	}

	if (pinNum == PIN_ANALOG_ACCEL_X) {

		//get analog value
		m_accel_valx = m_arduino.getAnalog(pinNum);
		//NEW
		m_accel_valx = (int)ofMap(m_accel_valx, xRawMin, xRawMax, -1000, 1000);
		float xAccel = m_accel_valx / 1000.0;

		if (xAccel > 0.28) {
			xDegreeTilt = 1;
			std::cout << " up " << std::endl;
		}
		else if (-0.1 < xAccel) {
			xDegreeTilt = 0;
			std::cout << " middle " + m_button_val << std::endl;
		}
		else {
			xDegreeTilt = -1;
			std::cout << " down " + m_button_val << std::endl;
		}
	}

	if (pinNum == PIN_ANALOG_ACCEL_Y) {

		//get analog value
		m_accel_valy = m_arduino.getAnalog(pinNum);
		m_accel_valy = (int)ofMap(m_accel_valy, yRawMin, yRawMax, -1000, 1000);
		float yAccel = m_accel_valy / 1000.0;
		if (yAccel > 0.5) {
			yDegreeTilt = -1;
			std::cout << " left " << std::endl;
		}
		else if (-0.5 < yAccel) {
			yDegreeTilt = 0;
			std::cout << " middle " << std::endl;
		}
		else {
			yDegreeTilt = 1;
			std::cout << " right " << std::endl;
		}

	}

	if (pinNum == PIN_ANALOG_ACCEL_Z) {

		//get analog value
		m_accel_valz = m_arduino.getAnalog(pinNum);
		m_accel_valz = (int)ofMap(m_accel_valz, 0, 1023, 0, 255);
	}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
