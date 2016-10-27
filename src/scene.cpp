#include "scene.h"

//NOTE: if you are unable to connect to your device on OS X, try unplugging and replugging in the power, while leaving the USB connected.
//ofxKinectV2 will only work if the NUI Sensor shows up in the Superspeed category of the System Profiler in the USB section.

//On OS X if you are not using the example project. Make sure to add OpenCL.framework to the Link Binary With Library Build Phase
//and change the line in Project.xcconfig to OTHER_LDFLAGS = $(OF_CORE_LIBS) $(OF_CORE_FRAMEWORKS) -framework OpenCL

//--------------------------------------------------------------
int scene::testFrequency = 2;
void scene::setup(){

    //Uncomment for verbose info from libfreenect2
    //ofSetLogLevel(OF_LOG_VERBOSE);

    //see how many devices we have.
    ofxKinectV2 tmp;
    vector <ofxKinectV2::KinectDeviceInfo> deviceList = tmp.getDeviceList();

    //allocate for this many devices
    kinects.resize(deviceList.size());
    //texDepth.resize(kinects.size());
    //texRGB.resize(kinects.size());


    //Note you don't have to use ofxKinectV2 as a shared pointer, but if you want to have it in a vector ( ie: for multuple ) it needs to be.
    for(int d = 0; d < kinects.size(); d++){
        kinects[d] = shared_ptr <ofxKinectV2> (new ofxKinectV2());
        kinects[d]->open(deviceList[d].serial);
      //  panel.add(kinects[d]->params);
    }
    SomeoneDetected = false;
    timer = false;
}

//--------------------------------------------------------------
void scene::update(){
        updateTimer();
        kinects[0]->update();
        if( kinects[0]->isFrameNew() ){
            if (!texDepth0.isAllocated()) {
              texDepth0 = kinects[0]->getDepthPixels();
              avg0 = getDepthAvg(texDepth0);

            }
            //std::cout << time << std::endl;
            if(!SomeoneDetected&&timer){
              timer = false;
              int avg = getDepthAvg(kinects[0]->getDepthPixels());
              if(avg>=avg0+10){
               std::cout << "someone is detected" << std::endl;
               SomeoneDetected = true;
              }
            }
            texDepth.loadData( kinects[0]->getDepthPixels() );
            texRGB.loadData( kinects[0]->getRgbPixels() );
        }
}

//--------------------------------------------------------------
void scene::draw(){
    //ofDrawBitmapString("ofxKinectV2: Work in progress addon.\nBased on the excellent work by the OpenKinect libfreenect2 team\n\n-Requires USB 3.0 port ( superspeed )\n-Requires patched libusb. If you have the libusb from ofxKinect ( v1 ) linked to your project it will prevent superspeed on Kinect V2", 10, 14);

        float dwHD = 1920/4;
        float dhHD = 1080/4;

        float shiftY = 100;// + ((10 + texDepth.getHeight()) * d);
        if (texDepth.isAllocated())
        texDepth.draw(0,0);

        //texRGB[d].draw(210 + texDepth[d].getWidth(), shiftY, dwHD, dhHD);


    //panel.draw();
}


int getDepthAvg(ofPixels pix){
  int i = 0;
  int avg = 0;
  for(i = 0; i < pix.size(); i+=100) {
    avg += (int)pix.getColor(i).r;
  }
  return int(avg*100/i);
}

int lasttime = 0;
void scene::updateTimer() {
   int currenttime = int(ofGetElapsedTimef());
   if((currenttime%testFrequency==0)&&currenttime!=lasttime){
     lasttime = currenttime;
     timer = true;
   }
}
