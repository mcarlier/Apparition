#include "scene.h"
#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
 #endif



//NOTE: if you are unable to connect to your device on OS X, try unplugging and replugging in the power, while leaving the USB connected.
//ofxKinectV2 will only work if the NUI Sensor shows up in the Superspeed category of the System Profiler in the USB section.

//On OS X if you are not using the example project. Make sure to add OpenCL.framework to the Link Binary With Library Build Phase
//and change the line in Project.xcconfig to OTHER_LDFLAGS = $(OF_CORE_LIBS) $(OF_CORE_FRAMEWORKS) -framework OpenCL

//--------------------------------------------------------------
int scene::testFrequency = 1;
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
    shader.load("shaders/shaderDetection");


    SomeoneDetected = 0;
    timer = false;
    move = false;
    saveImg = false;
}

//--------------------------------------------------------------
void scene::update(){
        updateTimer();
        kinects[0]->update();
        if( kinects[0]->isFrameNew() ){
            if (!texDepthRight0.isAllocated()) {
              texDepthRight0 = kinects[0]->getDepthPixels();
              texDepthLeft0.clone(texDepthRight0);
              texDepthLeft0.crop(0,0,texDepthLeft0.getWidth()/2,texDepthLeft0.getHeight());
              texDepthRight0.crop(texDepthRight0.getWidth()/2,0,texDepthRight0.getWidth()/2,texDepthRight0.getHeight());
              texRGBRight0 = kinects[0]->getRgbPixels();
              texRGBLeft0.clone(texRGBRight0);
              texRGBLeft0.crop(0,0,texRGBLeft0.getWidth()/2,texRGBLeft0.getHeight());
              texRGBRight0.crop(texRGBRight0.getWidth()/2,0,texRGBRight0.getWidth()/2,texRGBRight0.getHeight());
              plane.set(texRGBRight0.getWidth()/2, texRGBRight0.getHeight(), 10, 10);
              plane.mapTexCoords(0, 0, texRGBLeft0.getWidth(), texRGBLeft0.getHeight());
              avgR0 = getDepthAvg(texDepthRight0);
              avgL0 = getDepthAvg(texDepthLeft0);

            }



            //each second If noone is detected
            //  if((SomeoneDetected==0)&&timer){
            ofPixels currentDepthImg = kinects[0]->getDepthPixels();
            ofPixels currentRGBImg = kinects[0]->getRgbPixels();
            if(timer){
              detectPresence(currentDepthImg);
              lastRGBImage = currentRGBImg;
              timer = false;
              if (SomeoneDetected!=0){
                  //detectMotionRGB(currentRGBImg);
              }
             }
             if (SomeoneDetected!=0){
                 detectMotionDepth(currentDepthImg);
                 //detectMotionRGB(currentRGBImg);
             }
             else{
               chronoSave = 0;
               move = false;
             }

            texDepth.loadData( kinects[0]->getDepthPixels() );
            texRGB.loadData( kinects[0]->getRgbPixels() );
            if(SomeoneDetected!=0)
            saveImage(currentRGBImg);
        }
}

//--------------------------------------------------------------
void scene::draw(){
    //ofDrawBitmapString("ofxKinectV2: Work in progress addon.\nBased on the excellent work by the OpenKinect libfreenect2 team\n\n-Requires USB 3.0 port ( superspeed )\n-Requires patched libusb. If you have the libusb from ofxKinect ( v1 ) linked to your project it will prevent superspeed on Kinect V2", 10, 14);

        float dwHD = 1920/4;
        float dhHD = 1080/4;

        float shiftY = 100;// + ((10 + texDepth.getHeight()) * d);
        ofClear ( 0, 0, 0 );
        shader.begin();
        ofScale(ofVec3f(0.25));
        if(move){
          ofSetColor(ofColor::red);
        }
        else if (SomeoneDetected == 0) {
          ofSetColor(ofColor::white);
        }
        else if (SomeoneDetected == 1){
            ofSetColor(ofColor::blue);
        }
       else{
           ofSetColor(ofColor::green);
      }
        ofScale(ofVec3f(2));
        //std::cout << SomeoneDetected << std::endl;
        ofTranslate(-texRGB.getWidth()/2,-texRGB.getHeight()/2,0);
        if(saveImg==false){
          if (texRGB.isAllocated())
          texRGB.draw(0,0);//texRGB.draw(0,0);
        }
        else{
          testSave.draw(0,0);
        }
        ofScale(ofVec3f(2));
        shader.end();
        //texRGB[d].draw(210 + texDepth[d].getWidth(), shiftY, dwHD, dhHD);
      //panel.draw();
}

void scene::detectPresence(ofImage img){
  //std::cout << "Presence" << std::endl;
  int avgR,avgL;
  ofImage imgR;
  imgR.clone(img);
  img.crop(0,0,img.getWidth()/2,img.getHeight());
  imgR.crop(imgR.getWidth()/2,0,imgR.getWidth()/2,imgR.getHeight());
  Boolean someoneRight = false;
  Boolean someoneLeft = false;

    avgR= getDepthAvg(imgR);
    if(avgR>=avgR0+10){
     someoneRight = true;
     SomeoneDetected = 1;
     lastDepthImage = imgR;
    }

    avgL= getDepthAvg(img);
    if(avgL>=avgR0+10){
     someoneLeft = true;
     SomeoneDetected = 2;
     lastDepthImage = img;
    }

    if((someoneLeft&&someoneRight)||(!someoneLeft&&!someoneRight)){
      SomeoneDetected = 0;
    }

}
//
void scene::detectMotionDepth(ofImage img){
  if (SomeoneDetected==1) {
    img.crop(img.getWidth()/2,0,img.getWidth()/2,img.getHeight());
  }
  else{
    img.crop(0,0,img.getWidth()/2,img.getHeight());
  }
  for(int i = 0; i < img.getPixels().size(); i+=50) {
    img.setColor(i,img.getColor(i) -lastDepthImage.getColor(i));
  }
  if(getDepthAvg(img)>5){
    chronoSave = 0;
    move = true;
  }
  else{
    if(move == true){
      chronoSave = int(ofGetElapsedTimef());
    }
    move = false;
  }
}

//Fonction à adapter quand le projet sera dans un vrai projet.
void scene::saveImage(ofImage img){
    //std::cout << "crono"<<chronoSave << std::endl;
    //std::cout << int(ofGetElapsedTimef()) - chronoSave << std::endl;
     if((chronoSave!=0)&&(int(ofGetElapsedTimef()) - chronoSave>5) && !saveImg){
       std::cout << "SaveImg!" << std::endl;
       //char cCurrentPath[FILENAME_MAX];
       //GetCurrentDir("/Users/Maelle/Desktop/Mirai/of_v0.9.3_osx_release/", sizeof(cCurrentPath));
       string cCurrentPath;
       if(SomeoneDetected==1){
         cCurrentPath = "/Users/Maelle/Desktop/Mirai/of_v0.9.3_osx_release/examples/3d/wireframeDrawer/bin/data/imgRight.jpg";
       }
       else{
         cCurrentPath = "/Users/Maelle/Desktop/Mirai/of_v0.9.3_osx_release/examples/3d/wireframeDrawer/bin/data/imgLeft.jpg";
       }
       saveImg = true;
       ofSaveImage(img,cCurrentPath,OF_IMAGE_QUALITY_BEST);
       if(SomeoneDetected==1){
         testSave.load("imgRight.jpg");
       }
       else{
         testSave.load("imgLeft.jpg");
        }

     }
}
//Not working for now
void scene::detectMotionRGB(ofImage img){
  if (SomeoneDetected==1) {
    img.crop(img.getWidth()/2,0,img.getWidth()/2,img.getHeight());
  }
  else{
    img.crop(0,0,img.getWidth()/2,img.getHeight());
  }
  int firstavg =getDepthAvg(img);
  for(int i = 0; i < img.getPixels().size(); i+=3000) {
    img.setColor(i,img.getColor(i) -lastRGBImage.getColor(i));

  }

  if(getDepthAvg(img)>100){
    move = true;
  }
}


//Essayer e reduire le nombre de calcule ici;
int getDepthAvg(ofPixels pix){

  int i =0;
  int avg = 0;
  for( i = 0; i < pix.size(); i+=100) {

    avg += (int)pix.getColor(i).b;
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
