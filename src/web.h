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

		//Vbo dealing :
		ofVbo vboSusu;
		vector <ofVec3f> pointsSusu;
		vector <ofVec3f> sizesSusu;
		ofTexture texture;
		ofShader shaderSusu;

		//ofVbo vboWeb;



		//apprearance
		void setup_appeared();
		void update_appeared();
		ofxDelaunay triangulation;
		ofMesh mesh;
		int triangleDrawn;
		vector<ofMeshFace> triangles;




};
