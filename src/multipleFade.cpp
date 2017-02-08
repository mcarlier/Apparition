#include "multipleFade.h"
int multipleFade::numberOfImages;

void multipleFade::setup(int curentUserID, ofMesh triangulatedMesh,Json::Value jsoninfos){
  durationFade =stoi(jsoninfos["timerFade"].asString());
  durationStay=stoi(jsoninfos["timerStay"].asString());
  indice = 0;

  shaderF.load("shaders/fadeMultiple");
  currentId = curentUserID;
  int i = currentId%numberOfImages;
  if(curentUserID<numberOfImages){infTonumberOfImage=true;}
  else{infTonumberOfImage=false;}
  while (images.size()<numberOfImages) {
    ofImage img;
    img.load("img"+to_string(i)+".jpg");
    images.push_back(img);
    status.push_back(0);
    ofxSimpleTimer timer;
    timer.setup(durationFade);
    timers.push_back(timer);
    needToSeeBg = false;
    i++;
    i%=numberOfImages;
  }
  pauseBeforeBegin.setup(stoi(jsoninfos["pauseBeforeBegin"].asString()));
  isRunning = false;
  started = false;
  mesh = triangulatedMesh;
}
void multipleFade::start(){
  std::cout << currentId <<" >= "<< numberOfImages<< '\n';
  if(infTonumberOfImage&&(currentId>=numberOfImages)){
    infTonumberOfImage=false;
  }
  if(!infTonumberOfImage){//4 first users = normals
    isRunning = true;
    pauseBeforeBegin.start(false);
    restarted = true;
  }
  started = true;
  currentId++;

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
  //std::cout << "id = "<<id<<" time = "<<timers[id].getNormalizedProgress() << '\n';
  if(status[id]==1&&(timers[id].getNormalizedProgress()>=0.98||timers[id].getNormalizedProgress()<0)){
    status[id]=2;
    timers[id].stop();
    timers[id].setup(durationStay);
    timers[id].start(false);
    startNext();
     //std::cout << "2/ id = "<<id << '\n';
  }
  else if(status[id]==2&&(timers[id].getNormalizedProgress()>=0.98||timers[id].getNormalizedProgress()<0)){
    status[id]=3;
    timers[id].stop();
    timers[id].setup(durationFade);
    timers[id].start(false);
     //std::cout << "3/ id = "<<id << '\n';
  }
  else if(status[id]==3&&(timers[id].getNormalizedProgress()>=0.98||timers[id].getNormalizedProgress()<0)){
    status[id]=4;
     //std::cout << "4/ id = "<<id << '\n';
    checkEnd();
  }

}
void multipleFade::draw(ofShader shader,float currentTime){
  // ofPushMatrix();
  // ofTranslate(-images[0].getWidth()/4,images[0].getHeight()*0.75/2,0);
  // ofScale(ofVec3f(0.8));
  // ofScale(ofVec3f(images[0].getHeight()/424));
  // ofRotate(180,1,0,0);
  ofPushMatrix();
  ofScale(ofVec3f(0.65));
  ofTranslate(-images[0].getWidth()/2,-images[0].getHeight()/2,0);
  ofSetColor(ofColor::white);
  for (size_t i = 0; i < status.size(); i++) {
    if(status[i]!=0&&status[i]!=4)
      {
      shaderF.begin();
      shaderF.setUniform1f("u_time", currentTime);
      shaderF.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
      if(status[i]==1){
        shaderF.setUniform1f("timer", 1-timers[i].getNormalizedProgress());
      }
      else if(status[i]==2){
        shaderF.setUniform1f("timer", 0);
      }
      else if(status[i]==3){
        shaderF.setUniform1f("timer", timers[i].getNormalizedProgress());
      }
     images[i].draw(0,0);
    //  bind();
     //
    //   mesh.draw();
    //   images[i].unbind();
      shaderF.end();
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
    restarted=false;
  }
}
void multipleFade::startAnew(ofImage newImage){
  if(restarted==false){
    indice = 0;
    images.push_back(newImage);
    images.erase(images.begin());
    needToSeeBg=false;
    for (size_t i = 0; i < status.size(); i++) {
      status[i]=0;
      timers[i].stop();
    }
    restarted=true;
  }
}
void multipleFade::startNext(){
  if(indice<numberOfImages){
    if(status[indice]==0){
      status[indice]=1;
      timers[indice].start(false);
      std::cout << "start : " <<indice<< '\n';
    }
    indice ++;
  }
}
