#pragma once
#include "ofMain.h"
#include "triangleIntersect.h"

class susuwatari{
	public:
		void setup(ofVec3f newStart,ofVec3f newEnd,int indexVertex);
		void update();
		void draw();
		void setacceleration();
		Boolean betweenStartAndEnd();
		void changeDirection(ofVec3f newDirection, int indexVertex);
		void drawNormalEnd(ofVec3f normal);
		Boolean testNextPosition(ofMesh mesh, int indexVertex);
		void drawPath();
    float speed;
		ofVec3f start;
		ofVec3f end;
		int indexEnd;
		ofVec3f position;
		ofVec3f deplacement;
    ofMesh path;
};
