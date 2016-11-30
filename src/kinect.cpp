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
    base = kinect.getRgbPixels();
    base.save("emptyRoom.jpg");//Update : No need
    lastStateDetection = 0;
    stateDetection = 0;
    changeState = 0;
    shader.load("shaders/susu");

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

void kinect::saveImage(){
  //ofSaveImage(texRGB, string path,OF_IMAGE_QUALITY_BEST);
  texRGB.save("img.jpg");
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
