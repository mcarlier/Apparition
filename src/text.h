#pragma once
#include "ofMain.h"


class text {
	public:
		void setup(string count);
		void update(string count);
		void draw(Boolean waitToGo, Boolean end, int statSusu);

    ofTrueTypeFont myfont;
		string numberOfuser;
};
