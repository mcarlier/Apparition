#pragma once
#include "ofMain.h"
#include "susuwatari.h"

class web{
	public:
		void setup();
		void update();
		void draw();
		void calcNormals();
    float speed;
    ofMesh mesh;
		susuwatari susu;
};
