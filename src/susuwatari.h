#pragma once
#include "ofMain.h"


class susuwatari{
	public:
		void setup(ofMeshFace points);
		void update();
		void drawSusu();
		void drawWeb();
		void drawCurrentPath();
		void drawSegments();
		void reachEnd();
		void reachStart();
		int state; //0 change goal, 1 draw first edge, 2 draw 2nd edge, 3 draw third edge
		ofMeshFace currentTriangle;
		vector<ofPoint> segments;
		void addTriangle(ofMeshFace points);
		void changeStatus(int newStatus);
		void printTriangle();
		Boolean needToReachStart;
    float speed;
		ofVec3f start;
		ofVec3f end;
		ofVec3f direction;
		ofVec3f toStart;
		ofVec3f position;
    ofMesh meshCross;
};
