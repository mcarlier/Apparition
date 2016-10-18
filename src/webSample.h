#pragma once
#include "ofMain.h"


class webSample{
	public:
		//webSample.cpp general funcions
		ofVec3f position;
		float speed;
		ofMesh mesh;
		void setup();
		void update();
		void draw();

		vector<ofPoint> segments;
		void drawSusu();
		void drawWeb();
		void drawSegments();


		//webSample_appeared apprearance functions
		int state_appeared; //0 change goal, 1 draw first edge, 2 draw 2nd edge, 3 draw third edge
		ofMeshFace currentTriangle_appeared;
		Boolean needToReachstart_appeared;
		ofVec3f start_appeared;
		ofVec3f end_appeared;
		ofVec3f direction_appeared;
		ofVec3f tostart_appeared;

		void setup_appeared(ofMeshFace points);
		void drawCurrentPath_appeared();
		void update_appeared();
		void changeStatus_appeared(int newStatus);
		void reachEnd_appeared();
		void reachStart_appeared();
		void addTriangle_appeared(ofMeshFace points);

};
