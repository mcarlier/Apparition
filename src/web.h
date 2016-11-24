#pragma once
#include "ofMain.h"
#include "webSample.h"
#include "ofxDelaunay.h"

class web : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		void draw_rest();
		void update_rest();
		void changeState();
		int state;
		vector<webSample> webSamples;
		int NumWebSample;
		ofxDelaunay triangulation;

		//Vbo dealing :
		// ofVbo vboSusu;
		vector <ofVec2f> pointsSusu;
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
		void draw_appeard();
		int triangleDrawn;
		vector<ofMeshFace> triangles;

};
bool sortDescending(ofMeshFace i, ofMeshFace j);
