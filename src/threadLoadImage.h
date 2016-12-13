#pragma once
#include "ofThread.h"
#include "ofMain.h"

//Thread to load an image
class threadLoadImage: public ofThread
{
public:
    void start(){
      imageReady = false;
      startThread();
    }
    void stop(){ stopThread(); }

    void threadedFunction()
    {
      ofLoadImage(imageLoaded, "img.jpg");
      imageReady = true;
      // while (imageReady) {
      //
      // }
    };

    ofPixels imageLoaded;
    Boolean imageReady;
};
