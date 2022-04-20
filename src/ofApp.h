#pragma once

#include "ofMain.h"
#include "ofEvents.h"
#include "GameObject.h"
#include "GameObjectLink.h"


namespace config {
	static const std::string ARDUINO_DEVICE_NAME = "COM3";		//WIN
	//static const std::string ARDUINO_DEVICE_NAME = "/dev/cu.usbmodem144101";	//MAC
};

//#include "ofxAssimpModelLoader.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		//emily 
		static const int PIN_ANALOG_ACCEL_Z = 0;
		static const int PIN_ANALOG_ACCEL_Y = 1;
		static const int PIN_ANALOG_ACCEL_X = 2;
		static const int PIN_ANALOG_INPUTX = 3;
		static const int PIN_ANALOG_INPUTY = 4;
		static const int PIN_DIGITAL_INPUT = 2;
		static const int PIN_AUDIO_TOGGLE = 3;
		static const int PIN_PWM_OUTPUT = 9;

		int xRawMin = 415;
		int xRawMax = 653;

		int yRawMin = 405;
		int yRawMax = 590;

		int zRawMin = 490;
		int zRawMax = 612;

		int yDegreeTilt;
		int xDegreeTilt;

		bool mapButtonPress;
		bool mapVisibilty;

		bool audioButtonPress;
		//bool audioVisibilty;
		//Arduino stuff
		ofArduino				m_arduino;
		ofTrueTypeFont          m_font;
		int					    m_input_valy;	//sensor value
		int					    m_input_valx;	//sensor value
		int					    m_accel_valx;	//accelorometor value
		int					    m_accel_valy;	//accelorometor value
		int					    m_accel_valz;	//accelorometor value
		int					    m_button_val;	//map button value
		int					    m_audio_toggle_val;	//accelorometor value
		bool					m_bSetup;       //is Arduinio initialized yet
		void setupArduino(const int & _version);
		void updateArduino();
		void digitalPinChanged(const int & pinNum);
		void analogPinChanged(const int & pinNum);

		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofEasyCam cam;

		ofImage bg; 
		float bgMov;

		ofImage kite1; 
		ofImage kite2;
		ofImage kite3;
		ofImage currentKite; 
		
		ofImage cliff1;

		float layer1Mov;

		ofImage cliff2;
		float layer2Mov;

		ofImage cliff3;
		float layer3Mov;


		//layer 1 is the layer closest,
		//layer 2 is default 
		//layer 3 is furthest 
		enum modes {layer1, layer2, layer3}; 
		modes currentMode; 

		enum winState { play, won };
		winState currentWinState; 

		GameObject player; 
		GameObject bgImg;
		GameObject bgImg2;

		int currentZoom; 
		void zoom(int zoomFactor); 
		
		ofImage m_Star1;
		ofImage m_Star2;
		ofImage m_Star3;
		int StarsCollected; 

		GameObjectList Star1;
		GameObjectList Star2;
		GameObjectList Star3;

		GameObjectList Cliff1_1;
		GameObjectList Cliff1_2;
		GameObjectList Cliff1_3;
		
		GameObjectList Cliff2_1;
		GameObjectList Cliff2_2;
		GameObjectList Cliff2_3;

		GameObjectList Cliff3_1;
		GameObjectList Cliff3_2;
		GameObjectList Cliff3_3;


		ofTrueTypeFont pixelFont;

		void reset(float* num, GameObject* Object); 
		void resetStars(float* num, GameObjectList* Object);

		ofImage m_miniMap1;
		ofImage m_miniMap2;
		ofImage m_miniMap3;

		void speed(float speedChange);
		float currentSpeed;

		ofSoundPlayer  backgroundSound;
		ofSoundPlayer  hitSound;
		ofSoundPlayer  starSound;
		ofSoundPlayer  winSound;
		bool mute;



};
