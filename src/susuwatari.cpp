#include "susuwatari.h"

void susuwatari::setup(vector<ofPoint> points){
  state = 0;
  position = points[0];
  addTriangle(points);
  needToReachStart = false;
  speed = 1;
}

//--------------------------------------------------------------
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

void susuwatari::draw(){
  //ofSetColor(ofColor::green);
  //ofDrawLine(start,end);
  //drawPath();
  ofSetColor(ofColor::yellow);
  ofDrawTriangle(currentTriangle[0],currentTriangle[1],currentTriangle[2]);
  ofSetColor(ofColor::green);
  ofDrawSphere(start.x, start.y, start.z, 2);
  ofSetColor(ofColor::red);
  ofDrawSphere(end.x, end.y, end.z, 2);
  ofSetColor(ofColor::black);
  ofDrawSphere(position.x, position.y, position.z, 5);

}

void susuwatari::addTriangle(vector<ofPoint> points){
  if(end.length()-points[0].length()!=0){
    needToReachStart = true;
    toStart = points[0]-position;
  }
  //meshCross.addTriangle(currentTriangle);
  currentTriangle = points;
  printTriangle();
  changeStatus(1);
}
void susuwatari::changeStatus(int newStatus){
  if (newStatus==0){

  }
  else if (newStatus==1){
    start = currentTriangle[0];
    end = currentTriangle[1];
    direction = end - start;
    direction.normalize();
  }
  else if (newStatus==2){
    start = currentTriangle[1];
    end = currentTriangle[2];
    direction = end - start;
    direction.normalize();

  }
  else if (newStatus==3){
    start = currentTriangle[2];
    end = currentTriangle[0];
    direction = end - start;
    direction.normalize();

  }
  // else if (newStatus==4){
  // //  start = currentTriangle[0];
  // //  end = currentTriangle[1]; new triangle start.
  // }
  state = newStatus;
}


// void susuwatari::setacceleration(){
//   deplacement =end-start;
//   deplacement.normalize();
// }
//
void susuwatari::reachEnd(){
  ofVec3f PS,ES;
  PS = position-start;
  ES = end - start ;
  if(PS.length()>ES.length()){
     position = end;
     changeStatus((state+1)%4);
   }
}
void susuwatari::reachStart(){
  ofVec3f PS;
  PS = position-start;
  if(PS.dot(toStart) >= 0){
    needToReachStart = false;
  }

}
void susuwatari::printTriangle(){
  std::cout << currentTriangle[0]<< currentTriangle[1]<< currentTriangle[2] << std::endl;
}

// void susuwatari::changeDirection(ofVec3f newDirection, int indexVertex){
//   start = end;
//   path.addVertex(start);
//   position = end;
//   indexEnd = indexVertex;
//   end = newDirection;
//   setacceleration();
// }
//
// void susuwatari::drawPath(){
//   ofSetColor(ofColor::black);
//   for(int i = 0; i < path.getNumVertices()-1; i++) {
//    	ofDrawLine(path.getVertex(i),path.getVertex(i+1));
//   }
//   ofDrawLine(start,position);
//   //std::cout << path.hasNormals() << std::endl;
//   // ofSetColor(ofColor::black);
//   // for(int i = 0; i < path.getNumVertices()-1; i++) {
//   //   ofDrawLine(path.getVertex(i),path.getVertex(i+1));
//   // }
// }
