#pragma once
#include "ofThread.h"
#include "ofMain.h"


class threadSaveImage: public ofThread
{
public:
    void start(ofImage img,string path){
      nameImg = path;
      imageToSave = img;

      startThread();
    }
    void stop(){ stopThread(); }

    void threadedFunction()
    { std::cout << "save "<<nameImg<< '\n';
      imageToSave.save(nameImg);
    };

    string nameImg;
    ofImage imageToSave;
};
