#include "web.h"
int essai = 0;
void web::setup(){
  state = 0;

  NumWebSample = int(ofRandom(1,6));
  shaderSusu.load("shaders/shaderNoise");

  for (size_t i = 0; i < NumWebSample; i++) {
    webSample su;
    su.setup();
    webSamples.push_back(su);
  }
  shaderWeb.load("shaders/shader");


  positionMesh=1;
  if(positionMesh==1){
    RVB.load("imgRight.jpg");
    Depth.load("imgDRight.jpg");
  }
  else{
    RVB.load("imgLeft.jpg");
    Depth.load("imgDLeft.jpg");
  }
  createMesh();

  receiver.setup( PORT );
}
//--------------------------------------------------------------
void web::update(){
  if(state==1){
    update_appeared();
  }

  if(receiver.hasWaitingMessages()){
    ofxOscMessage m;
    receiver.getNextMessage( &m );
    string msg_string;
    msg_string = m.getAddress();
    msg_string += ": ";
    msg_string += m.getArgTypeName(0);
    msg_string += ":";
    msg_string += ofToString( m.getArgAsInt32(0) );
    std::cout << msg_string << std::endl;
  }
}

void web::draw(){

  ofScale(ofVec3f(0.65));
  ofTranslate(-RVB.getWidth()/2,-RVB.getHeight()/2,0);
  RVB.draw(0,0);
  ofTranslate(RVB.getWidth()/2,RVB.getHeight()/2,0);
  ofScale(ofVec3f(1/0.65));

  //RightSide
  if(positionMesh==1){
    ofPushMatrix();
    ofTranslate(0,RVB.getHeight()*0.75/2,0);
    ofScale(ofVec3f(0.8));
    ofScale(ofVec3f(RVB.getHeight()/Depth.getHeight()));
    ofRotate(180,1,0,0);
    ofSetColor(ofColor::purple);
    shaderWeb.begin();
    RVB.bind();
    for (size_t i = 0; i < webSamples.size(); i++) {
       webSamples[i].mesh.draw();
    }
    RVB.unbind();
    shaderWeb.end();
    for (size_t i = 0; i < webSamples.size(); i++) {
       webSamples[i].drawSusu();  }
    ofPopMatrix();
  }
  else{

    ofPushMatrix();
    ofTranslate(-Depth.getWidth()*1.9,RVB.getHeight()*0.75/2,0);
    ofScale(ofVec3f(0.8));
    ofScale(ofVec3f(RVB.getHeight()/Depth.getHeight()));
    ofRotate(180,1,0,0);
    ofSetColor(ofColor::purple);
    shaderWeb.begin();
    RVB.bind();
    for (size_t i = 0; i < webSamples.size(); i++) {
       webSamples[i].mesh.draw();
    }
    RVB.unbind();
    shaderWeb.end();
    for (size_t i = 0; i < webSamples.size(); i++) {
       webSamples[i].drawSusu();  }
    ofPopMatrix();
    shaderWeb.end();
    ofPopMatrix();
    }
}

//UPDATE  a optimiser en une seule boucle ajouter du random
void web::createMesh(){
  for (size_t i = 0; i < Depth.getWidth(); i+=10){//int(ofRandom(10,20))) {
      for (size_t j = 0; j < Depth.getHeight()-45; j+=10){//int(ofRandom(10,20))) {
        if(Depth.getColor(i,j).r>200){
          triangulation.addPoint(ofPoint(i,j,0));
          }
      }
  }
  triangulation.triangulate();
  for (size_t i = 0; i < Depth.getWidth(); i+=10){//=int(ofRandom(10,20))) {
      for (size_t j = 0; j < Depth.getHeight()-45; j+=10){//=int(ofRandom(10,20))) {
        if(Depth.getColor(i,j).r>200){
          if(positionMesh==1){
          triangulation.triangleMesh.addTexCoord(ofPoint(959+i*(RVB.getWidth()*0.42/Depth.getWidth()), -82 + j * (RVB.getHeight()*1.23 / Depth.getHeight())));
          }
          else{
          triangulation.triangleMesh.addTexCoord(ofPoint(209+i*(RVB.getWidth()*0.42/Depth.getWidth()), -85 + j * (RVB.getHeight()*1.23 / Depth.getHeight())));
          }

          }
      }
  }

}

void web::changeState(){
  state++;
  if(state==1){
    setup_appeared();
  }
}
