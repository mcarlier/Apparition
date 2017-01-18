#pragma once

#include "ofMain.h"
#include "ofxKinectV2.h"
#include "threadDetection.h"
#include "ofxSimpleTimer.h"
#include "threadSaveImage.h"
#include "threadLoadImage.h"



class kinect {

	public:
		ofxKinectV2 kinect;

		void setup(int precisionP,int precisionM);
		Boolean initialisationSucces;

		void update();
		void draw(ofShader shader,float currentTime);

    ofImage texRGB;
		ofImage base;

    threadDetection threadDetection;
		void updateState();
		int stateDetection;////0 = no detection/ 1 = someone //-1 someone moving
		int lastStateDetection;
		int changeState;


		threadLoadImage threadLoadImage;
		void loadNewImage();
		int loadState; //0needTolaunchThread,1 isLoading,2imageisReady;
		ofImage imageLoaded;



		threadSaveImage threadSaveImage;
		void saveImage(int userNumber);
		ofxSimpleTimer timerSaveBase;
		Boolean saveBase;

};
