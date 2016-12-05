#pragma once

#include "ofMain.h"
#include "ofxKinectV2.h"
#include "threadDetection.h"
#include "ofxSimpleTimer.h"
#include "threadSaveImage.h"
#include "threadLoadImage.h"



class kinect {

	public:
		void setup();
		void update();
		void draw(ofShader shader);

		Boolean initialisationSucces;
		ofxKinectV2 kinect;
    ofImage texRGB;
		ofImage base;
    threadDetection threadDetection;
		threadSaveImage threadSaveImage;
		threadLoadImage threadLoadImage;
		int loadState; //0needTolaunchThread,1 isLoading,2imageisReady;
		ofImage imageLoaded;
		void loadNewImage();

		int stateDetection;
		int lastStateDetection;
		int changeState;
		void updateState();
		void saveImage();
		//ofShader shader;

		ofxSimpleTimer timerSaveBase;
		Boolean saveBase;
};
