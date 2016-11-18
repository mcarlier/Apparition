#include "web.h"
int essai = 0;
void web::setup(){
  state = 0;

  NumWebSample = int(ofRandom(1,6));

  for (size_t i = 0; i < NumWebSample; i++) {
    webSample su;
    su.setup();
    webSamples.push_back(su);
  }
  shaderWeb.load("shaders/desappeare2");
  shaderSusu.load("shaders/susu");



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

}
//--------------------------------------------------------------
void web::update(){
  if(state==1){
    update_appeared();
  }

}

void web::draw(){

  //RightSide
  if(positionMesh==1){
    ofPushMatrix();
    ofTranslate(0,RVB.getHeight()*0.75/2,0);
    ofScale(ofVec3f(0.8));
    ofScale(ofVec3f(RVB.getHeight()/Depth.getHeight()));
    ofRotate(180,1,0,0);
    ofSetColor(ofColor::white);
    shaderWeb.begin();
    shaderWeb.setUniform1f("u_time", ofGetElapsedTimef());
    shaderWeb.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
    RVB.bind();
    //triangulation.triangleMesh.draw();
    for (size_t i = 0; i < webSamples.size(); i++) {
       webSamples[i].mesh.draw();
    }
    RVB.unbind();
    shaderWeb.end();
    shaderSusu.begin();
    for (size_t i = 0; i < webSamples.size(); i++) {
       webSamples[i].drawSusu();
     }
    shaderSusu.end();
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

//UPDATE : une seule boucle
void web::createMesh(){
  vector<ofPoint> textcoord;

  for (size_t j = 0; j < Depth.getHeight()-45; j+=10){
    for (size_t i = 0; i < Depth.getWidth(); i+=10){
        if(Depth.getColor(i,j).r>200){
          int a,b;
          if(i<=Depth.getWidth()/2){a = - ofRandom(0,10);}
          else{a =  ofRandom(0,5);}
          if(j<=Depth.getHeight()/2){b = -ofRandom(0,10);}
          else{b = -ofRandom(0,5);}
          triangulation.addPoint(ofPoint(i+a,j+b,0));
            if(positionMesh==1){
            textcoord.push_back(ofPoint(959+(i+a)*(RVB.getWidth()*0.42/Depth.getWidth()), -82 + (b+j) * (RVB.getHeight()*1.23 / Depth.getHeight())));
            }
            else{
              textcoord.push_back(ofPoint(209+(i+a)*(RVB.getWidth()*0.42/Depth.getWidth()), -85 + (b+j) * (RVB.getHeight()*1.23 / Depth.getHeight())));
            }
          }
      }
  }
  triangulation.triangulate();
  for (size_t i = 0; i < textcoord.size(); i++) {
    triangulation.triangleMesh.addTexCoord(textcoord[i]);
  }
}

void web::changeState(){
  state++;
  if(state==1){
    setup_appeared();
  }
}
