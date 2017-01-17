#include "multipleFade.h"
int multipleFade::numberOfImages = 5;

void multipleFade::setup(int curentUserID, ofMesh triangulatedMesh){
  if(curentUserID>=numberOfImages){
    curentUserID%=numberOfImages;
  }
  indice = 0;
  while (images.size()<numberOfImages) {
    ofImage img;
    img.load("img"+to_string(curentUserID)+".jpg");
    //images.insert (images.begin(), img);
    images.push_back(img);
    status.push_back(0);
    ofxSimpleTimer timer;
    timer.setup(5000);
    timers.push_back(timer);
    curentUserID = (curentUserID+1)%numberOfImages;
    needToSeeBg = false;
  }
  pauseBeforeBegin.setup(5000);
  isRunning = false;
  started = false;
  mesh = triangulatedMesh;
}
void multipleFade::start(){
  isRunning = true;
  started = true;
  pauseBeforeBegin.start(false);
}

void multipleFade::update(){
  if (pauseBeforeBegin.getNormalizedProgress()>=0.98||pauseBeforeBegin.getNormalizedProgress()<0) {
    startNext();
    pauseBeforeBegin.stop();
  }
  for_each (timers.begin(), timers.end(), multipleFade::updateTimer);
  for (size_t i = 0; i < status.size(); i++) {
    updateStatus(i);
  }
}
void multipleFade::updateTimer(ofxSimpleTimer timer){
  timer.update();
}
void multipleFade::updateStatus(int id){
  if(status[id]==1&&(timers[id].getNormalizedProgress()>=0.98||timers[id].getNormalizedProgress()<0)){
    status[id]=2;
    timers[id].stop();
    timers[id].setup(1000);
    timers[id].start(false);
    startNext();
    // std::cout << "2/ id = "<<id << '\n';
  }
  else if(status[id]==2&&(timers[id].getNormalizedProgress()>=0.98||timers[id].getNormalizedProgress()<0)){
    status[id]=3;
    timers[id].stop();
    timers[id].setup(5000);
    timers[id].start(false);
    // std::cout << "3/ id = "<<id << '\n';
  }
  else if(status[id]==3&&(timers[id].getNormalizedProgress()>=0.98||timers[id].getNormalizedProgress()<0)){
    status[id]=4;
    // std::cout << "4/ id = "<<id << '\n';
    checkEnd();
  }

}
void multipleFade::draw(ofShader shader,float currentTime){
  ofPushMatrix();
  ofTranslate(-images[0].getWidth()/4,images[0].getHeight()*0.75/2,0);
  ofScale(ofVec3f(0.8));
  ofScale(ofVec3f(images[0].getHeight()/424));
  ofRotate(180,1,0,0);
  ofSetColor(ofColor::white);
  for (size_t i = 0; i < status.size(); i++) {
    if(status[i]!=0&&status[i]!=4)
      {
      shader.begin();
      shader.setUniform1f("u_time", currentTime);
      shader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
      if(status[i]==1){
        shader.setUniform1f("timer", 1-timers[i].getNormalizedProgress());
      }
      else if(status[i]==2){
        shader.setUniform1f("timer", 0);
      }
      else if(status[i]==3){
        shader.setUniform1f("timer", timers[i].getNormalizedProgress());
      }
     images[i].bind();

      mesh.draw();
      images[i].unbind();
      shader.end();
    }
  }

  ofPopMatrix();
}

void multipleFade::checkEnd(){
  int isItOver = 0;
  for (size_t i = 0; i < status.size(); i++) {
    if(status[i]==4){
      isItOver++;
    }
  }
  if (isItOver==numberOfImages-1){
    needToSeeBg = true;
  }
  else if (isItOver==numberOfImages){
    std::cout << "end multipleFade" << '\n';
    isRunning=false;
  }
}
void multipleFade::startAnew(ofImage newImage){
 indice = 0;
 images.insert (images.begin(), newImage);
 images.erase (images.begin()+images.size()-1);
 for (size_t i = 0; i < status.size(); i++) {
   status[i]=0;
 }

}
void multipleFade::startNext(){
  if(indice<numberOfImages){
    if(status[indice]==0){
      status[indice]=1;
      timers[indice].start(false);
      // std::cout << "start : " <<indice<< '\n';
    }
    indice ++;
  }
}
