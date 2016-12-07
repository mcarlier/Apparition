#pragma once
#include "ofMain.h"
#include "ofxGui.h"




class text {
	public:
		void setup(string count);
		void update(string count);
		void draw(Boolean waitToGo, Boolean end, int statSusu);

    ofTrueTypeFont myfont;
		ofImage pleasesitJPN;
		ofImage youwereJPN;
		ofImage userJPN;
		ofImage participationJPN;

		string user;
		int numberOfUser;
		ofxPanel gui;
		ofxFloatSlider a;
		ofxFloatSlider b;
		ofxFloatSlider c;
		ofxFloatSlider d;
		ofxFloatSlider e;
		ofxFloatSlider f;
		ofxFloatSlider g;
		ofxFloatSlider h;
		ofxFloatSlider i;
		ofxFloatSlider j;
		ofxFloatSlider k;
		ofxFloatSlider l;

};
