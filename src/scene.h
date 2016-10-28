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
		void detectMotion(ofImage img);
		void draw();

        ofxPanel panel;

        vector < shared_ptr<ofxKinectV2> > kinects;

				ofImage  texDepthRight0;
				ofImage  texDepthLeft0;
				ofImage  lastImage;
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
};

int getDepthAvg(ofPixels pix);
