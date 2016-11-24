#include "webSample.h"
int webSample::NumWebSample = 0;
void webSample::setup(){
  NumWebSample++;
  index = NumWebSample;
  position = ofVec3f(0);
  speed = 4;
  size =(rand()%3)+2;
}

void webSample::update(){
}

//draw sphere around the webSample.
void  webSample::drawSusu(){
  ofSetColor(ofColor::white);
  // float a = size*(abs(sin(position.x+size+ofGetElapsedTimef()))+0.8);
  float a = size;//*(abs(sin(position.x+size+ofGetElapsedTimef()))+0.8);
  // ofBoxPrimitive box;
  // box.set(a);
  // box.setPosition(position);
  // box.draw();
  ofDrawCircle(position.x,position.y,size);

  // ofDrawSphere(position.x, position.y, position.z, size*(abs(sin(position.x+size+ofGetElapsedTimef()))+0.8));
}

//Draw the web
void webSample::drawWeb(){
  ofSetColor(ofColor::black);
  mesh.drawWireframe();

  //drawSegments();

}


//draw lines crossed by the webSample to go from each new triangle.
void webSample::drawSegments(){
  // if (!segments.empty()) {
  //   for (int i = 0; i < segments.size()-2; i+=2) {
  //     ofDrawLine(segments[i],segments[i+1]);
  //   }
  //   if (!needToReachStart) {
  //     ofDrawLine(segments[segments.size() -2],segments[segments.size() -1]);
  //   }
  // }
}
