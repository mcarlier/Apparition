#pragma once
#include "ofMain.h"
#include "webSample.h"
#include "ofxDelaunay.h"

class web : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		void changeState();
		int state;
		vector<webSample> webSamples;
		int NumWebSample;
		ofxDelaunay triangulation;
		ofMesh mesh;

		//Vbo dealing :
		ofVbo vboSusu;
		vector <ofVec3f> pointsSusu;
		vector <ofVec3f> sizesSusu;
		ofTexture texture;
		ofShader shaderSusu;

		ofShader shaderWeb;

		ofImage RVB;
		ofImage Depth;
		ofImage RVB0;
		ofImage Depth0;
		ofMesh meshRight;
		ofxDelaunay triangulationRight;
		void createMesh();





		//apprearance
		void setup_appeared();
		void update_appeared();
		int triangleDrawn;
		vector<ofMeshFace> triangles;
		ofPlanePrimitive plane;

};
