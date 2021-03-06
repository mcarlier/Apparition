#include "kinect.h"

//Setup the kinect and wait for the first frame
void kinect::setup(int precisionP,int precisionM){
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
      threadDetection.MotionDetectionPrecision=precisionM;
      threadDetection.PresenceDetectionPrecision=precisionP;
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
}


//Update the kinect and the detection
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
        //threadSaveImage.start(base,"emptyRoom.jpg");//Update : No need
      }
    }
}

//Draw the camera image
void kinect::draw(ofShader shader,float currentTime){
  if (texRGB.isAllocated()){
    ofPushMatrix();
    ofScale(ofVec3f(0.65));
    ofTranslate(-texRGB.getWidth()/2,-texRGB.getHeight()/2,0);
    shader.begin();
    shader.setUniform1f("u_time", currentTime);
    shader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
    texRGB.draw(0,0);
    shader.end();
    ofPopMatrix();
  }
}

//Check if the detection find something
void kinect::updateState(){
  if (lastStateDetection!=stateDetection) {
    changeState = stateDetection;
  }
  else{
    changeState = -2;
  }
  lastStateDetection = stateDetection;
}

//Load the current "data/img.jpg" in a different thread
void kinect::loadNewImage(){
  if(loadState==0){
    threadLoadImage.start();
    loadState=1;
  }
  else if(loadState==1){
      if (threadLoadImage.imageReady){
      imageLoaded = threadLoadImage.imageLoaded;
      threadLoadImage.imageReady = false;
      threadLoadImage.stop();
      loadState=2;
    }
  }
}

//Save the current RGB image.
void kinect::saveImage(int userNumber){
  int num = userNumber%4;///UNPDa
  std::cout << "num = "<<num << '\n';
  threadSaveImage.start(texRGB,"img"+to_string(num)+".jpg");
  imageLoaded = texRGB;
}
