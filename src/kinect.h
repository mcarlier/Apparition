#pragma once

#include "ofMain.h"
#include "ofxKinectV2.h"
#include "threadDetection.h"
#include "ofxSimpleTimer.h"
#include "threadSaveImage.h"



class kinect {

	public:
		void setup();
		void update();
		void draw();

		Boolean initialisationSucces;
		ofxKinectV2 kinect;
    ofImage texRGB;
		ofImage base;
    threadDetection threadDetection;
		threadSaveImage threadSaveImage;

		int stateDetection;
		int lastStateDetection;
		int changeState;
		void updateState();
		void saveImage();
		ofShader shader;

		ofxSimpleTimer timerSaveBase;
		Boolean saveBase;
};
