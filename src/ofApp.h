#pragma once

#include "ofMain.h"
#include "web.h"
#include "kinect.h"
#include "sound.h"
#include "text.h"
#include "ofxSimpleTimer.h"
#include "jsonManager.h"
#include "ofxGui.h"







class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		void exit();
		void stateManager();
		void peopleOutManager();

		ofxSimpleTimer timerDetectionStill;
		ofxSimpleTimer timerPeopleOut;

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		jsonManager counterUser;
		ofEasyCam cam;
		web web;

		ofImage base;
		ofShader shader;
		kinect kinect;
		sound sound;
		text text;
		Boolean imageSaved;
		Boolean restart;

		void startAnew();
		ofxPanel gui;
		ofxFloatSlider radius;
		ofxFloatSlider random_base;
		ofxFloatSlider b;
		ofxFloatSlider c;


};
