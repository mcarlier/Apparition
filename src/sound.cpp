#include "sound.h"

void sound::setup(){
  	sound.load("husavikharbouredit.wav");
  	sound.setLoop(true);
  	sound.play();
  	fftSmoothed = new float[8192];
  	for (int i = 0; i < 8192; i++){
  		fftSmoothed[i] = 0;
  	}
  	nBandsToGet = 128;
}

//--------------------------------------------------------------

void sound::update(){
  float avg0 = 0;
  float * val = ofSoundGetSpectrum(nBandsToGet);
	for (int i = 0;i < nBandsToGet; i++){
    avg0+=fftSmoothed[i];
  	fftSmoothed[i] *= 0.96f;
  	if (fftSmoothed[i] < val[i]){
      fftSmoothed[i] = val[i];
    }
  }
  avg=avg0/nBandsToGet;
}

//--------------------------------------------------------------
void sound::draw(){
  float width = (float)(20*128) / nBandsToGet;
  for (int i = 0;i < nBandsToGet; i++){
    ofDrawRectangle(-620+i*width,350,width,-(fftSmoothed[i] * 200));
    ofDrawRectangle(-620+i*width,-350,width,(fftSmoothed[i] * 200));

  }
}
