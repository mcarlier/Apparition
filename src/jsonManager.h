#pragma once
#include "ofMain.h"
#include "ofxJSON.h"



class jsonManager {
	public:
		ofxJSONElement counterUser;

		void setup();
		void increment();
    int getInt();
    string getString();

};
