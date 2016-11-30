#pragma once
#include "ofMain.h"
#include "webSample.h"
#include "ofxDelaunay.h"
#include "ofxGui.h"
#include "ofxSimpleTimer.h"


class web {
	public:
		void setup();
		void update();
		void draw(float soundeffect);
		void drawSusus(float soundeffect);
		void draw_web();
		void changeState(int newState); // 0 = rest,1 = detected 2 = drawing;
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

		ofImage RVB;
		void createMesh();
		Boolean meshcomplete;

		Boolean meshDesappear;
		ofShader Desappeare;
		void makeMeshDesappeare();
		ofxSimpleTimer timerMeshDesappeare ;

		Boolean end;
		void updateEnd();
		void setupEnd();
		ofShader shaderEnd;
		ofImage base;




		int triangleDrawn;
		vector<ofMeshFace> triangles;

};
bool sortDescending(ofMeshFace i, ofMeshFace j);
