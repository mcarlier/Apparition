#pragma once

#include "ofMain.h"
#include "ofxKinectV2.h"
#include "ofxGui.h"

class scene {

	public:
		void setup();
		void update();
		void updateTimer();
		void detectPresence(ofImage img);
		void detectMotionDepth(ofImage img);
		void detectMotionRGB(ofImage img);
		void draw();

        ofxPanel panel;

        vector < shared_ptr<ofxKinectV2> > kinects;

				ofImage  texDepthRight0;
				ofImage  texRGBRight0;
				ofImage  texDepthLeft0;
				ofImage  texRGBLeft0;
				ofImage  lastRGBImage;
				ofImage  lastDepthImage;
				int avgR0,avgL0;
				ofTexture texDepth;
        ofTexture texRGB;
				int SomeoneDetected;//0 = no detection/ 1 = right / 2 = left;
				Boolean timer;
				static int testFrequency;

				ofShader shader;
				ofPlanePrimitive plane;
				ofImage diff;
				Boolean move;

				Boolean saveImg;
				int chronoSave;
				void saveImage(ofImage img,ofImage imgdepth);
				ofImage testSave;

};

int getDepthAvgPresence(ofPixels pix);
int getDepthAvgMotion(ofPixels pix);
