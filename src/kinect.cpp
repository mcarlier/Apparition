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
    saveBase = false;
    timerSaveBase.setup(2000);
    timerSaveBase.start(false);
    lastStateDetection = 0;
    stateDetection = 0;
    changeState = 0;
    loadState = 0;
    shader.load("shaders/susu");

}

//--------------------------------------------------------------

void kinect::update(){
    if(initialisationSucces){
      timerSaveBase.update();
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
      if (!timerSaveBase.bIsRunning&&!saveBase) {
        saveBase=true;
        base = kinect.getRgbPixels();
        threadSaveImage.start(base,"emptyRoom.jpg");//Update : No need
      }
    }
}

void kinect::saveImage(){
  //ofSaveImage(texRGB, string path,OF_IMAGE_QUALITY_BEST);
  threadSaveImage.start(texRGB,"img.jpg");//Update : No need

}
void kinect::loadNewImage(){
  if(loadState==0){
    threadLoadImage.start();
    loadState=1;
  }
  else if(loadState==1){
      if (threadLoadImage.imageLoaded.isAllocated()) {
      imageLoaded = threadLoadImage.imageLoaded;
      threadLoadImage.stop();
      loadState=2;
    }


  }
}
//--------------------------------------------------------------
void kinect::draw(){
  if (texRGB.isAllocated()){
    ofPushMatrix();
    ofScale(ofVec3f(0.65));
    ofTranslate(-texRGB.getWidth()/2,-texRGB.getHeight()/2,0);
    shader.begin();
    texRGB.draw(0,0);
    shader.end();
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
