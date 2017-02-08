#include "threadDetection.h"
// int threadDetection::MotionDetectionPrecision;
// int threadDetection::PresenceDetectionPrecision;

void threadDetection::setup(ofPixels img){
    currentDepthImage = img;
    avg0 = getDepthAvgPresence(currentDepthImage);
    SomeoneDetected = 0;
    move = false;
}

void threadDetection::update(ofPixels img){
      move = false;

      detectPresence(img);

      lastDepthImage = img;
};


//Detect if someone is in the room
void threadDetection::detectPresence(ofPixels img){
    int avg;
    avg= getDepthAvgPresence(img);
    if(abs(avg-avg0)>=20){
      SomeoneDetected = 1;
    }
    else{
      SomeoneDetected = 0;
    }
}

//Detect if something moved since the last frame
void threadDetection::detectMotion(ofPixels imgDepth){
  int diffDepth = 0;
  int i;
  for(i = 0; i < imgDepth.size(); i+=100) {
    if(imgDepth.getColor(i).r!=lastDepthImage.getColor(i).r){
      diffDepth++;
    }
  }
  std::cout <<diffDepth<<" "<<i << '\n';
  if(diffDepth>MotionDetectionPrecision){
    move = true;
  }
}

int threadDetection::getDetectionStatus(){
  return move*(-2*SomeoneDetected) + SomeoneDetected;
}

int threadDetection::getDepthAvgPresence(ofPixels pix){
  int avg = 0;
  int diffDepth = 0;

  for(int i = 0; i < pix.size(); i+=100) {
    if ((int)pix.getColor(i).r<PresenceDetectionPrecision) {
      avg ++;
    }
   if (SomeoneDetected!=0){
      if(pix.getColor(i).r!=lastDepthImage.getColor(i).r){
        diffDepth++;
      }
    }
  }
  if(diffDepth!=0)std::cout <<diffDepth<< '\n';
  if(diffDepth>MotionDetectionPrecision){
    move = true;
  }
  return avg;
}
