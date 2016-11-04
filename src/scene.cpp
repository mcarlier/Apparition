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
              avgR0 = getDepthAvgPresence(texDepthRight0);
              avgL0 = getDepthAvgPresence(texDepthLeft0);

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
                //detectMotionDepth(currentDepthImg);
                //detectMotionRGB(currentRGBImg);
              }
             }
             if (SomeoneDetected!=0){
                 //detectMotionDepth(currentDepthImg);
                 //detectMotionRGB(currentRGBImg);
             }
             else{
               chronoSave = 0;
               move = false;
               std::cout << "noone" << std::endl;
             }

            texDepth.loadData( kinects[0]->getDepthPixels() );
            texRGB.loadData( kinects[0]->getRgbPixels() );
            if(SomeoneDetected!=0)
            saveImage(currentRGBImg,currentDepthImg);
        }
}

//--------------------------------------------------------------
void scene::draw(){
    //ofDrawBitmapString("ofxKinectV2: Work in progress addon.\nBased on the excellent work by the OpenKinect libfreenect2 team\n\n-Requires USB 3.0 port ( superspeed )\n-Requires patched libusb. If you have the libusb from ofxKinect ( v1 ) linked to your project it will prevent superspeed on Kinect V2", 10, 14);
        ofPushMatrix();
        ofClear ( 0, 0, 0 );
        shader.begin();
        ofScale(ofVec3f(0.65));
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
        //std::cout << SomeoneDetected << std::endl;
        ofTranslate(-texRGB.getWidth()/2,-texRGB.getHeight()/2,0);
        //if(SomeoneDetected==0){
          if (texRGB.isAllocated())
          texRGB.draw(0,0);
          texDepth.draw(0,0);

        //}
        //else{
          // testSave
          // texRGB.draw(0,0);
          // texDepth.draw(0,0);

          //testSave.draw(0,0);
        //}
        shader.end();
        //texRGB[d].draw(210 + texDepth[d].getWidth(), shiftY, dwHD, dhHD);
      //panel.draw();
      ofPopMatrix();
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

    avgR= getDepthAvgPresence(imgR);
    if(abs(avgR-avgR0)>=20){
     someoneRight = true;
     SomeoneDetected = 1;
     lastDepthImage = imgR;
    }

    avgL= getDepthAvgPresence(img);
    if(abs(avgL-avgL0)>=20){
     someoneLeft = true;
     SomeoneDetected = 2;
     lastDepthImage = img;
    }
    std::cout << "myenne generaleR"<<avgR0 << " "<< avgR << std::endl;
    std::cout << "myenne generaleL"<<avgL0 << " "<< avgL << std::endl;
    std::cout << SomeoneDetected << std::endl;

    if(someoneLeft&&someoneRight){
      if (avgR>avgL) {
        SomeoneDetected=1;
      }
    }
    if(!someoneLeft&&!someoneRight){
      SomeoneDetected = 0;
    }

}
//
void scene::detectMotionDepth(ofImage img){
  if (SomeoneDetected==1) {
    img.crop(img.getWidth()/2,0,img.getWidth()/2,img.getHeight());
    lastDepthImage.crop(lastDepthImage.getWidth()/2,0,lastDepthImage.getWidth()/2,lastDepthImage.getHeight());

  }
  else{
    img.crop(0,0,img.getWidth()/2,img.getHeight());
    lastDepthImage.crop(0,0,lastDepthImage.getWidth()/2,lastDepthImage.getHeight());

  }
  int avg = 0;
  std::cout << getDepthAvgMotion(img) <<"  "<<getDepthAvgMotion(lastDepthImage)<< std::endl;
  for(int i = 0; i < img.getPixels().size(); i+=50) {
    if(img.getColor(i)!=lastDepthImage.getColor(i)){
      avg ++;
    }
    int a = abs(img.getColor(i).r -lastDepthImage.getColor(i).r);
    img.setColor(i,ofColor(a,a,a));
  }
  std::cout << getDepthAvgMotion(img) << std::endl;
  std::cout <<"avg" <<avg<< std::endl;

  if(getDepthAvgMotion(img)>5){
    chronoSave = 0;
    move = true;
  }
  else{
    if(move == true){
      chronoSave = int(ofGetElapsedTimef());
    }
    move = false;
  }
  testSave = img;
}

//Not working for now
void scene::detectMotionRGB(ofImage img){
  if (SomeoneDetected==1) {
    img.crop(img.getWidth()/2,0,img.getWidth()/2,img.getHeight());
    lastRGBImage.crop(lastRGBImage.getWidth()/2,0,lastRGBImage.getWidth()/2,lastRGBImage.getHeight());

  }
  else{
    img.crop(0,0,img.getWidth()/2,img.getHeight());
    lastRGBImage.crop(0,0,lastRGBImage.getWidth()/2,lastRGBImage.getHeight());

  }
  int firstavg =getDepthAvgMotion(img);
  for(int i = 0; i < img.getPixels().size(); i+=3000) {
    img.setColor(i,img.getColor(i) -lastRGBImage.getColor(i));

  }

  if(getDepthAvgMotion(img)>100){
    move = true;
  }
  testSave = img;
}

//Fonction à adapter quand le projet sera dans un vrai projet.
void scene::saveImage(ofImage img,ofImage imgdepth){
    //std::cout << "crono"<<chronoSave << std::endl;
    //std::cout << int(ofGetElapsedTimef()) - chronoSave << std::endl;
     if((chronoSave!=0)&&(int(ofGetElapsedTimef()) - chronoSave>5) && !saveImg){
       std::cout << "SaveImg!" << std::endl;
       //char cCurrentPath[FILENAME_MAX];
       //GetCurrentDir("/Users/Maelle/Desktop/Mirai/of_v0.9.3_osx_release/", sizeof(cCurrentPath));
       string cCurrentPath;
       string cCurrentPathd;
       if(SomeoneDetected==1){
         cCurrentPath = "/Users/Maelle/Desktop/Mirai/of_v0.9.3_osx_release/examples/3d/wireframeDrawer/bin/data/imgRight.jpg";
         cCurrentPathd = "/Users/Maelle/Desktop/Mirai/of_v0.9.3_osx_release/examples/3d/wireframeDrawer/bin/data/imgDRight.jpg";
         ofSaveImage(texDepthRight0,"/Users/Maelle/Desktop/Mirai/of_v0.9.3_osx_release/examples/3d/wireframeDrawer/bin/data/texDepthRight0.jpg",OF_IMAGE_QUALITY_BEST);
         ofSaveImage(texRGBRight0,"/Users/Maelle/Desktop/Mirai/of_v0.9.3_osx_release/examples/3d/wireframeDrawer/bin/data/texRGBRight0.jpg",OF_IMAGE_QUALITY_BEST);

       }
       else{
         cCurrentPath = "/Users/Maelle/Desktop/Mirai/of_v0.9.3_osx_release/examples/3d/wireframeDrawer/bin/data/imgLeft.jpg";
         cCurrentPathd = "/Users/Maelle/Desktop/Mirai/of_v0.9.3_osx_release/examples/3d/wireframeDrawer/bin/data/imgDLeft.jpg";
         ofSaveImage(texDepthLeft0,"/Users/Maelle/Desktop/Mirai/of_v0.9.3_osx_release/examples/3d/wireframeDrawer/bin/data/texDepthLeft0.jpg",OF_IMAGE_QUALITY_BEST);
         ofSaveImage(texRGBLeft0,"/Users/Maelle/Desktop/Mirai/of_v0.9.3_osx_release/examples/3d/wireframeDrawer/bin/data/texRGBLeft0.jpg",OF_IMAGE_QUALITY_BEST);

       }
       saveImg = true;
       ofSaveImage(img,cCurrentPath,OF_IMAGE_QUALITY_BEST);
       ofSaveImage(imgdepth,cCurrentPathd,OF_IMAGE_QUALITY_BEST);
      //  if(SomeoneDetected==1){
      //    testSave.load("imgRight.jpg");
      //  }
      //  else{
      //    testSave.load("imgLeft.jpg");
      //   }

     }
}

//Essayer e reduire le nombre de calcule ici;
int getDepthAvgPresence(ofPixels pix){

  int i =0;
  int avg = 0;
  for( i = 0; i < pix.size(); i+=100) {
    // int a = ((int)pix.getColor(i).b-i);
    // avg += a*a;
    if ((int)pix.getColor(i).r<200) {
      avg ++;
    }
  }
  return avg;//int(avg*100/i);
}

int getDepthAvgMotion(ofPixels pix){

  int i =0;
  int avg = 0;
  for( i = 0; i < pix.size(); i+=100) {
    //int a = ((int)pix.getColor(i).b-i);
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
