#pragma once

#include "ofMain.h"
#include "ofxKinectV2.h"
#include "threadDetection.h"


class kinect {

	public:
		void setup();
		void update();
		void draw();

		Boolean initialisationSucces;
		ofxKinectV2 kinect;
    ofImage texRGB;
    threadDetection threadDetection;
		int stateDetection;
};
