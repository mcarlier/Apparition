#pragma once
#include "ofMain.h"
#include "ofxSimpleTimer.h"

class faceAppeare {

	public:
		void setup(int duration,ofMeshFace points, int t);
    ofMesh lastFace;
    ofxSimpleTimer timerappearance;
		Boolean canDraw;
		int type;//1 : silhouette //2 : end
};
