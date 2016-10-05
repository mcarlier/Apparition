#pragma once
#include "ofMain.h"
#include "susuwatari.h"
#include "ofxDelaunay.h"

class web : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		//void calcNormals();
		susuwatari susu;
		ofxDelaunay triangulation;
		int triangleDrawn;
};
