#pragma once

#include "ofMain.h"
#include "ofxKinectV2.h"
#include "ofxGui.h"

class scene {

	public:
		void setup();
		void update();
		void updateTimer();
		void draw();

        ofxPanel panel;

        vector < shared_ptr<ofxKinectV2> > kinects;

				ofPixels  texDepth0;
				int avg0;
				ofTexture texDepth;
        ofTexture texRGB;
				Boolean SomeoneDetected;
				Boolean timer;
				static int testFrequency;
};

int getDepthAvg(ofPixels pix);
