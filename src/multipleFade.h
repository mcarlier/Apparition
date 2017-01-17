#pragma once
#include "ofMain.h"
#include "ofxSimpleTimer.h"





class multipleFade {
	public:
		static int numberOfImages;
		void setup(int curentUserID,ofMesh triangulatedMesh);
		void update();
		static void updateTimer(ofxSimpleTimer timer);
		void updateStatus(int id);
		void draw(ofShader shader,float currentTime);
    void start();
		void startNext();
		void checkEnd();
		void startAnew(ofImage newImage);

		ofxSimpleTimer pauseBeforeBegin;
    vector<ofImage> images;
		vector<int> status; //0 not started, 1 fadeIn, 2 Pause, 3 fadeOut, 4 finished
    vector<ofxSimpleTimer> timers;
    ofShader shader;
		ofMesh mesh;
    Boolean isRunning;
		Boolean needToSeeBg;
    Boolean started;
		int indice;
};
