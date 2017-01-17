#pragma once
#include "ofMain.h"
#include "webSample.h"
#include "ofxDelaunay.h"
#include "ofxGui.h"
#include "ofxSimpleTimer.h"
#include "multipleFade.h"


class web {
	public:
		void setup(string lastuserID);
		void setupEnd();

		void update();
		void updateEnd();

		void draw(ofShader shader,ofShader shaderweb,float soundeffect,float currentTime);
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

		multipleFade multipleFade;
		ofxSimpleTimer timerMeshDesappeare;


		Boolean waitPeopleToGo;
		Boolean setupWaitPeopleToGo;
		Boolean end;
		Boolean meshDesappear;
		Boolean meshcomplete;

		ofShader shaderEnd;
		ofShader Desappeare;

		ofImage base;
		ofImage RVB;

		ofxPanel gui;
		ofxFloatSlider a;
		ofxFloatSlider d;
		ofxFloatSlider b;
		ofxFloatSlider c;

};
bool sortDescending(ofMeshFace i, ofMeshFace j);
