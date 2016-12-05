#pragma once
#include "ofMain.h"
#include "ofxJSON.h"



class jsonManager {
	public:
		void setup();
    int getInt();
    string getString();
    void increment();

    ofxJSONElement counterUser;
};
