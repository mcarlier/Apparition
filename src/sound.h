#pragma once

#include "ofMain.h"



class sound {

	public:
		void setup();
		void update();
		void draw();

    ofSoundPlayer  sound;
    float * fftSmoothed;
    int nBandsToGet;
		float avg;
};
