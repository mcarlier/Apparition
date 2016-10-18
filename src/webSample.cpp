#include "webSample.h"

void webSample::setup(){
  position = ofVec3f(0);
  speed = 10;
}

void webSample::update(){
}

//draw sphere around the webSample.
void  webSample::drawSusu(){
  ofSetColor(ofColor::white);
  ofDrawSphere(position.x, position.y, position.z, 5);
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
