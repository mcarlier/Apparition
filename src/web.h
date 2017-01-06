#pragma once
#include "ofMain.h"
#include "webSample.h"
#include "ofxDelaunay.h"
#include "ofxGui.h"
#include "ofxSimpleTimer.h"


class web {
	public:
		void setup();
		void setupEnd();

		void update();
		void updateEnd();

		void draw(ofShader shader,float soundeffect,float currentTime);
		void drawSusus(ofShader shader,float soundeffect,float currentTime);
		void draw_web(ofShader shader,float currentTime);
		void draw_fadetriangles(float currentTime);

		void changeState(int newState); // 0 = rest,1 = detected 2 = drawing;
		int state;

		void createMesh();
		void increaseSpeed();
		void makeMeshDesappeare();
		void startAnew(ofImage newImg);

		int NumWebSample;
		vector<webSample> webSamples;
		vector<ofMeshFace> triangles;
		vector <ofVec2f> pointsSusu;
		ofxDelaunay triangulation;
		int triangleDrawn;

		ofxSimpleTimer timerMeshDesappeare ;

		Boolean waitPeopleToGo;
		Boolean setupWaitPeopleToGo;
		Boolean end;
		Boolean meshDesappear;
		Boolean meshcomplete;

		ofShader shaderEnd;
		ofShader Desappeare;

		ofImage base;
		ofImage RVB;

};
bool sortDescending(ofMeshFace i, ofMeshFace j);
