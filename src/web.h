#pragma once
#include "ofMain.h"
#include "susuwatariGroup.h"
#include "ofxDelaunay.h"

class web : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

		susuwatariGroup susuwataris;

		ofxDelaunay triangulation;
		ofMesh mesh;
		float rotation;
		int triangleDrawn;
		vector<ofMeshFace> triangles;

};
