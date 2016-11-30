#pragma once
#include "ofThread.h"
#include "ofMain.h"


class threadDetection: public ofThread
{
public:
    void start(){ startThread();}
    void stop(){ stopThread(); }
    void setup(ofPixels img);
    void update(ofPixels img);

    ofPixels  currentDepthImage;
    ofPixels  lastDepthImage;
    int avg0;
    int SomeoneDetected;//0 = no detection/ 1 = right / 2 = left;
    Boolean move;

    int MotionDetectionPrecision = 900;
    int PresenceDetectionPrecision = 200;

    void draw(){};
    void detectPresence(ofPixels img);
    int getDepthAvgPresence(ofPixels pix);
    void detectMotion(ofPixels img);
    int getDetectionStatus();

    void threadedFunction()
    {
        while(isThreadRunning())
        {
          if (lock()) {
            ofPixels img = currentDepthImage;
            update(img);
            unlock();
          }
          sleep(1000);
        }
    };
};
