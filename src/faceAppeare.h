#pragma once
#include "ofMain.h"
#include "ofxSimpleTimer.h"

class faceAppeare {

	public:
		void setup(int duration,ofMeshFace points);
    ofMesh lastFace;
    ofxSimpleTimer timerappearance;
};
