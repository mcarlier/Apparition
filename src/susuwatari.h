#pragma once
#include "ofMain.h"
#include "ofxDelaunay.h"


class susuwatari{
	public:
		void setup(vector<ofPoint> points);
		void update();
		void draw();
		void drawCurrentPath();
		void drawSegments();
		//void setacceleration();
		void reachEnd();
		void reachStart();
		//void changeDirection(ofVec3f newDirection, int indexVertex);
		//void drawNormalEnd(ofVec3f normal);
		//void drawPath();
		int state; //0 change goal, 1 draw first edge, 2 draw 2nd edge, 3 draw third edge
		vector<ofPoint> currentTriangle;
		vector<ofPoint> segments;
		void addTriangle(vector<ofPoint> points);
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
