#pragma once
#include "ofMain.h"
#include "webSample.h"
#include "ofxDelaunay.h"

#include "ofxOsc.h"

// listen on port 12345
#define PORT 12345
#define NUM_MSG_STRINGS 50

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

		//Vbo dealing :
		// ofVbo vboSusu;
		// vector <ofVec3f> pointsSusu;
		// vector <ofVec3f> sizesSusu;
		ofShader shaderSusu;
		ofShader shaderWeb;


		int positionMesh; //1 = right / 2 = left;
		ofImage RVB;
		ofImage Depth;
		void createMesh();



		//apprearance
		void setup_appeared();
		void update_appeared();
		int triangleDrawn;
		vector<ofMeshFace> triangles;

		ofxOscReceiver	receiver;
};
