#include "susuwatari.h"

void susuwatari::setup(ofMeshFace points){
  state = 0;
  position = points.getVertex(0);
  addTriangle(points);
  needToReachStart = false;
  speed = 10;
}

void susuwatari::update(){
  if(!needToReachStart){
    if(state!=0){
      position+= direction*speed;
      reachEnd();
    }
  }
  else{
    position +=toStart.normalize()*speed;
    reachStart();
  }
}

//draw sphere around the susuwatari.
void  susuwatari::drawSusu(){
  ofSetColor(ofColor::white);
  ofDrawSphere(position.x, position.y, position.z, 5);
}

//Draw the web
void susuwatari::drawWeb(){
  ofSetColor(ofColor::black);
  meshCross.drawWireframe();
  drawCurrentPath();
  //drawSegments();

}

//Draw the triangle that the susuwatari is drawing.
void susuwatari::drawCurrentPath(){
    if(state==1){
      if(needToReachStart==false){
        ofDrawLine(start,position);
      }
      else{
        ofDrawLine(segments[segments.size()-1],position);
      }
    }
    else if (state==2){
      ofDrawLine(currentTriangle.getVertex(0),currentTriangle.getVertex(1));
      ofDrawLine(start,position);

    }
    else if (state==3){
      ofDrawLine(currentTriangle.getVertex(0),currentTriangle.getVertex(1));
      ofDrawLine(currentTriangle.getVertex(1),currentTriangle.getVertex(2));
      ofDrawLine(start,position);
    }
}

//draw lines crossed by the susuwatari to go from each new triangle.
void susuwatari::drawSegments(){
  if (!segments.empty()) {
    for (int i = 0; i < segments.size()-2; i+=2) {
      ofDrawLine(segments[i],segments[i+1]);
    }
    if (!needToReachStart) {
      ofDrawLine(segments[segments.size() -2],segments[segments.size() -1]);
    }
  }
}

//Add triangle to the mesh when the drawing is end
void susuwatari::addTriangle(ofMeshFace points){
  if(end.length()-points.getVertex(0).length()!=0){
    needToReachStart = true;
    toStart = points.getVertex(0)-position;
    segments.push_back(points.getVertex(0));
    segments.push_back(position);
  }
  meshCross.addVertex(currentTriangle.getVertex(0));
  meshCross.addVertex(currentTriangle.getVertex(1));
  meshCross.addVertex(currentTriangle.getVertex(2));
  currentTriangle = points;
  changeStatus(1);
}

//0 change goal, 1 draw first edge, 2 draw 2nd edge, 3 draw third edge
void susuwatari::changeStatus(int newStatus){
  if (newStatus==0){
  }
  else if (newStatus==1){
    start = currentTriangle.getVertex(0);
    end = currentTriangle.getVertex(1);
    direction = end - start;
    direction.normalize();
  }
  else if (newStatus==2){
    start = currentTriangle.getVertex(1);
    end = currentTriangle.getVertex(2);
    direction = end - start;
    direction.normalize();
  }
  else if (newStatus==3){
    start = currentTriangle.getVertex(2);
    end = currentTriangle.getVertex(0);
    direction = end - start;
    direction.normalize();
  }
  state = newStatus;
}

//Test if the susuwatari excedded end position
void susuwatari::reachEnd(){
  ofVec3f PS,ES;
  PS = position-start;
  ES = end - start ;
  if(PS.length()>ES.length()){
     position = end;
     changeStatus((state+1)%4);
   }
}

// Test if the susuwatari reach her new Start
void susuwatari::reachStart(){
  ofVec3f PS;
  PS = position-start;
  if(PS.dot(toStart) >= 0){
    needToReachStart = false;
  }
}

//Print the vertices of the triangle that the susuwatari is currently drawing.
void susuwatari::printTriangle(){
  std::cout << currentTriangle.getVertex(0)<< currentTriangle.getVertex(1)<< currentTriangle.getVertex(2) << std::endl;
}
