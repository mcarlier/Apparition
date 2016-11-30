#pragma once
#include "ofMain.h"


class webSample{
	public:
		//webSample.cpp general funcions
		ofVec3f position;
		float speed;
		int size;
		ofMesh mesh;
		int index;
		static int NumWebSample;
		void setup();
		void update();
		void draw();
		void changeState(int newState);
		void clear();
		int state;

		ofMesh meshEnd;
		Boolean end;


		ofImage susuImg;


		void drawSusu(float sound);
		void drawWeb();

		Boolean needToReachstart;
		Boolean meshcomplete;
		ofVec3f start;
		ofVec3f tostart;
		void reachStart();


		//rest
		void setup_rest();
		void update_rest();


		//detected
		void setup_detected();
		void update_detected();

		//webSample_appeared apprearance functions
		void setup_appeared();
		void update_appeared();
		int state_appeared; //0 change goal, 1 draw first edge, 2 draw 2nd edge, 3 draw third edge
		ofMeshFace currentTriangle_appeared;
		ofVec3f start_appeared;
		ofVec3f end_appeared;
		ofVec3f direction_appeared;
		ofVec3f tostart_appeared;

		void changeStatus_appeared(int newStatus);
		void reachEnd_appeared();
		void reachStart_appeared();
		void addTriangle_appeared(ofMeshFace points);
};
