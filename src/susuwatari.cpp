#include "susuwatari.h"


void susuwatari::setup(ofVec3f newStart,ofVec3f newEnd, int indexVertex){
  speed = 2;
  indexEnd = indexVertex;
  start = newStart;
  position = newStart;
  end = newEnd;
  path.addVertex(start);
  setacceleration();

}

//--------------------------------------------------------------
void susuwatari::update(){
  position+= deplacement*speed;
}

void susuwatari::draw(){
  //ofSetColor(ofColor::green);
  //ofDrawLine(start,end);
  drawPath();
  ofSetColor(ofColor::black);
  ofDrawSphere(position.x, position.y, position.z, 5);
}

void susuwatari::setacceleration(){
  deplacement =end-start;
  deplacement.normalize();
}

Boolean susuwatari::betweenStartAndEnd(){
  if((start.dot(position)<=start.dot(end))){
    return false;
  }
  else{
    return true;
  }
}

void susuwatari::changeDirection(ofVec3f newDirection, int indexVertex){
  start = end;
  path.addVertex(start);
  position = end;
  indexEnd = indexVertex;
  end = newDirection;
  setacceleration();
}

void susuwatari::drawPath(){
  ofSetColor(ofColor::black);
  for(int i = 0; i < path.getNumVertices()-1; i++) {
   	ofDrawLine(path.getVertex(i),path.getVertex(i+1));
  }
  ofDrawLine(start,position);
  //std::cout << path.hasNormals() << std::endl;
  // ofSetColor(ofColor::black);
  // for(int i = 0; i < path.getNumVertices()-1; i++) {
  //   ofDrawLine(path.getVertex(i),path.getVertex(i+1));
  // }
}

void susuwatari::drawNormalEnd(ofVec3f  normal){
  ofSetColor(ofColor::blue);
  ofDrawLine(end, normal);
  // vector<ofVec3f> n = mesh.getNormals();
  // vector<ofVec3f> v = mesh.getVertices();
  // float normalLength = 5.;
  //
  // if(!ofGetKeyPressed()){
  //     ofSetColor(255,255,255,70);
  //     for(unsigned int i=0; i < n.size() ;i++){
  //         ofDrawLine(v[i].x,v[i].y,v[i].z,
  //                v[i].x+n[i].x*normalLength,v[i].y+n[i].y*normalLength,v[i].z+n[i].z*normalLength);
  //
  //         ofDrawLine(.98*v[i].x,.98*v[i].y,.98*v[i].z,
  //                .98*v[i].x+n[i].x*normalLength*.2,.98*v[i].y+n[i].y*normalLength*.2,.98*v[i].z+n[i].z*normalLength*.2);
  //         ofDrawLine(.98*v[i].x+n[i].x*normalLength*.2,.98*v[i].y+n[i].y*normalLength*.2,.98*v[i].z+n[i].z*normalLength*.2,
  //                v[i].x+n[i].x*normalLength*.2,v[i].y+n[i].y*normalLength*.2,v[i].z+n[i].z*normalLength*.2);
  //     }
  // }
}

Boolean susuwatari::testNextPosition(ofMesh mesh, int indexVertex){
  vector<ofMeshFace> triangles = mesh.getUniqueFaces();
  ofVec3f nextPosition = mesh.getVertex(indexVertex);
  ofVec3f direct = nextPosition-end;
  direct.normalize();
  triangle_intersection tri;
  float f =3;
  for (int i = 0; i < triangles.size(); i++) {
    Boolean aa = tri.test(triangles[i].getVertex(0),triangles[i].getVertex(1),triangles[i].getVertex(2), end,direct, &f);
    std::cout << i << std::endl;
    std::cout << aa << std::endl;
  //  std::cout <<  f<< std::endl;
}


  return true;

}
