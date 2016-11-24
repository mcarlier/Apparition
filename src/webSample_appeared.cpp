#include "webSample.h"
void webSample::setup_appeared(ofMeshFace points){
  state_appeared = 0;
  //position = points.getVertex(0);
  //addTriangle_appeared(points);
  needToReachstart_appeared = true;
  speed = 1;
}

void webSample::update_appeared(){
  if(!needToReachstart_appeared){
    if(state_appeared!=0){
      position+= direction_appeared*speed;
      reachEnd_appeared();
    }
  }
  else{
    position +=tostart_appeared.normalize()*speed;
    reachStart_appeared();
  }
}

//Draw the triangle that the webSample is drawing.
void webSample::drawCurrentPath_appeared(){
    if(state_appeared==1){
      if(needToReachstart_appeared==false){
        ofDrawLine(start_appeared,position);
      }
      else{
        ofDrawLine(segments[segments.size()-1],position);
      }
    }
    else if (state_appeared==2){
      ofDrawLine(currentTriangle_appeared.getVertex(0),currentTriangle_appeared.getVertex(1));
      ofDrawLine(start_appeared,position);

    }
    else if (state_appeared==3){
      ofDrawLine(currentTriangle_appeared.getVertex(0),currentTriangle_appeared.getVertex(1));
      ofDrawLine(currentTriangle_appeared.getVertex(1),currentTriangle_appeared.getVertex(2));
      ofDrawLine(start_appeared,position);
    }
}

//Add triangle to the mesh when the drawing is end_appeared
void webSample::addTriangle_appeared(ofMeshFace points){
  if(end_appeared.length()-points.getVertex(0).length()!=0){
    needToReachstart_appeared = true;
    tostart_appeared = points.getVertex(0)-position;
    segments.push_back(points.getVertex(0));
    segments.push_back(position);
  }
  mesh.addVertex(currentTriangle_appeared.getVertex(0));
  mesh.addTexCoord(currentTriangle_appeared.getTexCoord(0));
  mesh.addVertex(currentTriangle_appeared.getVertex(1));
  mesh.addTexCoord(currentTriangle_appeared.getTexCoord(1));
  mesh.addVertex(currentTriangle_appeared.getVertex(2));
  mesh.addTexCoord(currentTriangle_appeared.getTexCoord(2));

  currentTriangle_appeared = points;
  changeStatus_appeared(1);
}

//0 change goal, 1 draw first edge, 2 draw 2nd edge, 3 draw third edge
void webSample::changeStatus_appeared(int newStatus){
  if (newStatus==0){
  }
  else if (newStatus==1){
    start_appeared = currentTriangle_appeared.getVertex(0);
    end_appeared = currentTriangle_appeared.getVertex(1);
    direction_appeared = end_appeared - start_appeared;
    direction_appeared.normalize();
  }
  else if (newStatus==2){
    start_appeared = currentTriangle_appeared.getVertex(1);
    end_appeared = currentTriangle_appeared.getVertex(2);
    direction_appeared = end_appeared - start_appeared;
    direction_appeared.normalize();
  }
  else if (newStatus==3){
    start_appeared = currentTriangle_appeared.getVertex(2);
    end_appeared = currentTriangle_appeared.getVertex(0);
    direction_appeared = end_appeared - start_appeared;
    direction_appeared.normalize();
  }
  state_appeared = newStatus;
}

//Test if the webSample excedded end_appeared position
void webSample::reachEnd_appeared(){
  ofVec3f PS,ES;
  PS = position-start_appeared;
  ES = end_appeared - start_appeared ;
  if(PS.length()>ES.length()){
     position = end_appeared;
     changeStatus_appeared((state_appeared+1)%4);
   }
}

// Test if the webSample reach her new start_appeared
void webSample::reachStart_appeared(){
  ofVec3f PS;
  PS = position-start_appeared;
  if(PS.dot(tostart_appeared) >= 0){
    needToReachstart_appeared = false;
  }
}
