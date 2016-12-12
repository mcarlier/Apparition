#pragma once
#include "ofThread.h"
#include "ofMain.h"

//Thread to load an image
class threadLoadImage: public ofThread
{
public:
    void start(){
      imagePicktedUP = false;
      startThread();
    }
    void stop(){ stopThread(); }

    void threadedFunction()
    {
      ofLoadImage(imageLoaded, "img.jpg");
      if (imageLoaded.isAllocated()) {
      }
      while (!imagePicktedUP) {

      }
    };

    ofPixels imageLoaded;
    Boolean imagePicktedUP;
};
