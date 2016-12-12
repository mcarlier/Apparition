#include "webSample.h"
int webSample::NumWebSample = 0;

//Global setup
void webSample::setup(){
  NumWebSample++;
  index = NumWebSample;
  position = ofVec3f(0);
  speed = 6;
  size =(rand()%3)+2;
  susuImg.load("dot.png");
  end = false;
}

//Global update
void webSample::update(){
  if(state==2){
    update_appeared();
  }
  else if(state==1){
    update_detected();
  }
  else{
    update_rest();
  }
}

//draw the susu texture around the webSample position.
void  webSample::drawSusu(ofShader shader,float soundeffect){
  float a = 10*size + (soundeffect*1000)*5;
  shader.begin();
  susuImg.draw(position.x-(a/2),position.y-(a/2),a,a);
  shader.end();
}

//Change the state of the susu
void webSample::changeState(int newState){
  state = newState;
  if(state==0){
     setup_rest();
  }
  else if(state==1){
    setup_detected();
  }
  else if (state == 2){
    setup_appeared();
  }
}
//Reinitialise all the datas on webSample
void webSample::clear(){
  mesh.clear();
  ofMeshFace t;
  currentTriangle_appeared = t;
}
//Check if a susu is next triangles it'll draw
void webSample::reachStart(){
  ofVec3f direction = start-position;
  position +=direction.normalize()*speed;
  if (ofDist(start.x,start.y,position.x,position.y)<2) {
    needToReachstart = false;
  }
}
//Set up the rest state
void webSample::setup_rest(){
      needToReachstart = true;
}

void webSample::update_rest(){
  if(!needToReachstart){
    position.x=ofMap( ofNoise( (ofGetElapsedTimef() +(index)) ), 0, 5, 0, -700)+305;
    position.y=ofMap( ofNoise( (1000.0+ ofGetElapsedTimef())+index), 0, 1, 0, 157)+20;
  }
  else{
    start.x=ofMap(ofNoise( ofGetElapsedTimef() +(index) ), 0, 5, 0, -700)+305;
    start.y=ofMap(ofNoise( (1000.0+ ofGetElapsedTimef())+index), 0, 1, 0, 157)+20;
    reachStart();
  }
}
//sate up the detected state
void webSample::setup_detected(){
    needToReachstart = true;
}
//Update position in detected state
void webSample::update_detected(){
  if(!needToReachstart){
      position.x=ofMap(ofNoise( ofGetElapsedTimef() +(index) ), 0, 1, 0, -700)+570;
      position.y=ofMap(ofNoise((1000.0+ ofGetElapsedTimef())+index), 0, 1, 0, 157)+20;
  }
  else{
    start.x=ofMap(ofNoise( ofGetElapsedTimef() +(index) ), 0, 1, 0, -700)+570;
    start.y=ofMap(ofNoise((1000.0+ ofGetElapsedTimef())+index), 0, 1, 0, 157)+20;
    reachStart();
  }
}
//set up the appearance state
void webSample::setup_appeared(){
  state_appeared = 0;
  needToReachstart = true;
}
//update position in appearance state
void webSample::update_appeared(){
  if(!needToReachstart){
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
//Control the initialisation of a fade in/out triangles
void webSample::updatefaces(){
  for (int j = 0; j < faces.size(); j++) {
    if (faces[j].timerappearance.bIsRunning) {
      if (faces[j].timerappearance.getNormalizedProgress()>0.1) {
        faces[j].canDraw=true;
      }
    }
    else{
      if(!needToReachstart){
        faces[j].timerappearance.start(false);
      }
    }
  }
}

//Add the next triangle that will be draw
void webSample::addTriangle_appeared(ofMeshFace points){
  if(end_appeared.length()-points.getVertex(0).length()!=0){
    needToReachstart = true;
    tostart_appeared = points.getVertex(0)-position;
  }
  if(!end){
    chekFaceCompleted();
    faceAppeare f;
    f.setup(4000,points,1);
    faces.push_back(f);
  }
  else{
    chekFaceCompleted();
    faceAppeare f;
    f.setup(1000,points,2);
    faces.push_back(f);
  }
  currentTriangle_appeared = points;
  changeStatus_appeared(1);
}
// Chek if the fade in/out triangles are finished then add them to the correct mesh
void webSample::chekFaceCompleted(){
  for (int j = 0; j < faces.size(); j++) {
    if (faces[j].timerappearance.getNormalizedProgress()<=0) {
      if(faces[j].type==2){
        meshEnd.append(faces[j].lastFace);
      }
      else{
        mesh.append(faces[j].lastFace);
      }
      faces.erase(faces.begin()+j);
    }
  }
}
//change the status of the susu according of the progress across the triangle
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
    needToReachstart = false;
  }
}
