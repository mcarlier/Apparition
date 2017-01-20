#pragma once
#include "ofMain.h"
#include "ofxSimpleTimer.h"
#include "ofxJSON.h"






class multipleFade {
	public:
		static int numberOfImages;
		Boolean infTonumberOfImage;
		void setup(int curentUserID,ofMesh triangulatedMesh,Json::Value jsoninfos);
		void update();
		static void updateTimer(ofxSimpleTimer timer);
		void updateStatus(int id);
		void draw(ofShader shader,float currentTime);
    void start();
		void startNext();
		void checkEnd();
		void startAnew(ofImage newImage);

		ofxSimpleTimer pauseBeforeBegin;
		int durationFade;
		int durationStay;
    vector<ofImage> images;
		vector<int> status; //0 not started, 1 fadeIn, 2 Pause, 3 fadeOut, 4 finished
    vector<ofxSimpleTimer> timers;
    ofShader shader;
		ofMesh mesh;
    Boolean isRunning;
		Boolean needToSeeBg;
    Boolean started;
		Boolean restarted;
		int indice;
		int currentId;
};
