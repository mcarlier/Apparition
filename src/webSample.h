#pragma once
#include "ofMain.h"
#include "faceAppeare.h"
#include "ofxSimpleTimer.h"


class webSample{
	public:
		static int NumWebSample;

		void setup();
		void update();
		void drawSusu(ofShader shader,float sound);
		void changeState(int newState);
		void clear();

		ofVec3f position;
		float speed;
		int size;
		int index;
		int state;

		ofMesh mesh;
		ofMesh meshEnd;
		ofMesh lastFace;
		vector<faceAppeare> faces;

		Boolean end;
		Boolean needToReachstart;
		ofImage susuImg;

		void reachStart();
		ofVec3f start;
		ofVec3f tostart;

		//rest
		void setup_rest();
		void update_rest();

		//detected
		void setup_detected();
		void update_detected();

		//webSample_appeared apprearance functions
		void setup_appeared();
		void update_appeared();
		void updatefaces();
		void addTriangle_appeared(ofMeshFace points);
		void chekFaceCompleted();
		void changeStatus_appeared(int newStatus);
		int state_appeared; //0 change goal, 1 draw first edge, 2 draw 2nd edge, 3 draw third edge
		void reachEnd_appeared();
		void reachStart_appeared();
		ofMeshFace currentTriangle_appeared;
		ofVec3f start_appeared;
		ofVec3f end_appeared;
		ofVec3f direction_appeared;
		ofVec3f tostart_appeared;

};
