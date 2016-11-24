#include "web.h"
int essai = 0;
void web::setup(){
  state = 0;

  NumWebSample = 5;

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
  else{
    update_rest();
  }

}

void web::draw(){
  ofSetColor(ofColor(255,255,255,100));
  if(state==1){
    draw_appeard();
  }
  else{
    draw_rest();
  }



}

void web::update_rest(){
  for (size_t i = 0; i < webSamples.size(); i++) {
    std::cout << ofGetWidth()<<" "<< ofGetHeight() << '\n';
    std::cout << ofGetElapsedTimef() +(webSamples[i].index)  << '\n';
    webSamples[i].position.x=ofMap( ofNoise( ofGetElapsedTimef() +(webSamples[i].index) ), 0, 1, 0, -700)+350;
    webSamples[i].position.y=ofMap( ofNoise( (1000.0+ ofGetElapsedTimef())+(webSamples[i].index)), 0, 1, 0, 157)+50;

  }
}
void web::draw_rest(){
  ofPushMatrix();
  ofTranslate(0,RVB.getHeight()*0.75/2,0);
  ofScale(ofVec3f(0.8));
  ofScale(ofVec3f(RVB.getHeight()/Depth.getHeight()));
  ofRotate(180,1,0,0);

  for (size_t i = 0; i < webSamples.size(); i++) {
     webSamples[i].drawSusu();
   }
  ofPopMatrix();
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
  triangles = triangulation.triangleMesh.getUniqueFaces();
  ofSort(triangles,sortDescending); //order the triangles for the drawing
}
//Define the sort for ordering the drawing of the triangles
bool sortDescending(ofMeshFace i, ofMeshFace j)
{
    return (j.getVertex(0).y < i.getVertex(0).y);
}



void web::changeState(){
  state++;
  if(state==1){
    setup_appeared();
  }
}
