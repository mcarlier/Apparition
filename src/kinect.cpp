#include "kinect.h"

void kinect::setup(){

    //Uncomment for verbose info from libfreenect2
    //ofSetLogLevel(OF_LOG_VERBOSE);
    initialisationSucces = false;
    ofxKinectV2 tmp;
    vector <ofxKinectV2::KinectDeviceInfo> deviceList = tmp.getDeviceList();
    if(deviceList.size()!=0){
      initialisationSucces = true;
      kinect.open(deviceList[0].serial);
      while (kinect.isFrameNew() ==false) {
        kinect.update();
      }
      threadDetection.setup(kinect.getDepthPixels());
      threadDetection.startThread();
    }
    lastStateDetection = 0;
    stateDetection = 0;
    changeState = 0;

}

//--------------------------------------------------------------

void kinect::update(){
    if(initialisationSucces){
      kinect.update();
      if(kinect.isFrameNew()){
          texRGB = kinect.getRgbPixels();
          if (threadDetection.lock()) {
              threadDetection.currentDepthImage =  kinect.getDepthPixels();
              stateDetection = threadDetection.getDetectionStatus();
              threadDetection.unlock();
          }
      }
      updateState();
    }
}

//--------------------------------------------------------------
void kinect::draw(){
  if (texRGB.isAllocated()){
    ofPushMatrix();
    ofScale(ofVec3f(0.65));
    ofTranslate(-texRGB.getWidth()/2,-texRGB.getHeight()/2,0);
    texRGB.draw(0,0);
    ofPopMatrix();
  }
}

void kinect::updateState(){
  if (lastStateDetection!=stateDetection) {
    changeState = stateDetection;
  }
  else{
    changeState = -2;
  }
  lastStateDetection = stateDetection;
}
