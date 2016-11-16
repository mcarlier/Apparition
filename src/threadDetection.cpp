#include "threadDetection.h"

void threadDetection::setup(ofPixels img){
    currentDepthImage = img;
    ofPixels texDepthRight0 = img;
    ofPixels texDepthLeft0 = texDepthRight0;
    texDepthLeft0.crop(0,0,texDepthLeft0.getWidth()/2,texDepthLeft0.getHeight());
    texDepthRight0.crop(texDepthRight0.getWidth()/2,0,texDepthRight0.getWidth()/2,texDepthRight0.getHeight());
    avgR0 = getDepthAvgPresence(texDepthRight0);
    avgL0 = getDepthAvgPresence(texDepthLeft0);

    SomeoneDetected = 0;
    move = false;

}

void threadDetection::update(ofPixels img){
      move = false;
      if (SomeoneDetected!=0){
        detectMotion(img);
      }
       detectPresence(img);
       lastDepthImage = img;
};


//Detect if someone is in the room
void threadDetection::detectPresence(ofPixels img){
    int avgR,avgL;
    ofPixels imgR;
    imgR = img;
    img.crop(0,0,img.getWidth()/2,img.getHeight());
    imgR.crop(imgR.getWidth()/2,0,imgR.getWidth()/2,imgR.getHeight());
    Boolean someoneRight = false;
    Boolean someoneLeft = false;
    avgR= getDepthAvgPresence(imgR);
    if(abs(avgR-avgR0)>=20){
     someoneRight = true;
     SomeoneDetected = 1;
    }
    avgL= getDepthAvgPresence(img);
    if(abs(avgL-avgL0)>=20){
     someoneLeft = true;
     SomeoneDetected = 2;
    }
    if(someoneLeft&&someoneRight){
      if (avgR>avgL) {
        SomeoneDetected=1;
      }
    }
    if(!someoneLeft&&!someoneRight){
      SomeoneDetected = 0;
    }
}

//Detect if something moved since the last frame
void threadDetection::detectMotion(ofPixels imgDepth){
  if (SomeoneDetected==1) {
    imgDepth.crop(imgDepth.getWidth()/2,0,imgDepth.getWidth()/2,imgDepth.getHeight());
    lastDepthImage.crop(lastDepthImage.getWidth()/2,0,lastDepthImage.getWidth()/2,lastDepthImage.getHeight());

  }
  else{
    imgDepth.crop(0,0,imgDepth.getWidth()/2,imgDepth.getHeight());
    lastDepthImage.crop(0,0,lastDepthImage.getWidth()/2,lastDepthImage.getHeight());
  }
  int diffDepth = 0;
  for(int i = 0; i < imgDepth.size(); i+=100) {
    if(imgDepth.getColor(i).r!=lastDepthImage.getColor(i).r){
      diffDepth++;
    }
  }

  if(diffDepth>MotionDetectionPrecision){
    move = true;
  }
}

int threadDetection::getDetectionStatus(){
  return move*(-2*SomeoneDetected) + SomeoneDetected;
}

int threadDetection::getDepthAvgPresence(ofPixels pix){
  int avg = 0;
  for(int i = 0; i < pix.size(); i+=100) {
    if ((int)pix.getColor(i).r<PresenceDetectionPrecision) {
      avg ++;
    }
  }
  return avg;
}
