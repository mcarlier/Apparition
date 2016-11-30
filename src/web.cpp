#include "web.h"
int essai = 0;
void web::setup(){

  NumWebSample = 8;
  for (size_t i = 0; i < NumWebSample; i++) {
    webSample su;
    su.setup();
    webSamples.push_back(su);
  }
  changeState(0);
  shaderWeb.load("shaders/desappeare2");
  shaderSusu.load("shaders/susu");

  RVB.load("img.jpg");
  createMesh();
  meshcomplete = false;


}

//--------------------------------------------------------------
void web::update(){
  meshcomplete = true;
  for (size_t i = 0; i < webSamples.size(); i++) {
    if (webSamples[i].state==2) {
      if( webSamples[i].state_appeared == 0 && triangleDrawn < triangulation.getNumTriangles()){
        webSamples[i].addTriangle_appeared(triangles[triangleDrawn]);
        triangleDrawn ++;
      }
      else if ( webSamples[i].state_appeared == 0 && triangleDrawn >= triangulation.getNumTriangles()){
        webSamples[i].changeState(0);
        webSamples[i].meshcomplete=true;
      }
    }
    webSamples[i].update();
    if (webSamples[i].meshcomplete==false) {
      meshcomplete=false;
    }
  }
}

void web::draw(float soundeffect){
    ofSetColor(ofColor(255,255,255,100));
    draw_web();
    drawSusus(soundeffect);
}
void web::changeState(int newState){
  state = newState;
  triangleDrawn = 0;
  for (size_t i = 0; i < webSamples.size(); i++) {
    webSamples[i].changeState(newState);
  }
}


void web::draw_web(){
    ofPushMatrix();
    ofTranslate(-RVB.getWidth()/4,RVB.getHeight()*0.75/2,0);
    ofScale(ofVec3f(0.8));
    ofScale(ofVec3f(RVB.getHeight()/424));
    ofRotate(180,1,0,0);
    ofSetColor(ofColor::white);
    shaderWeb.begin();
    shaderWeb.setUniform1f("u_time", ofGetElapsedTimef());
    shaderWeb.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
    RVB.bind();
    if (meshcomplete) {
      triangulation.triangleMesh.drawWireframe();
    }
    else{
      for (size_t i = 0; i < webSamples.size(); i++) {
         webSamples[i].mesh.draw();
       }
    }
    RVB.unbind();
    shaderWeb.end();
    ofPopMatrix();
}

void web::drawSusus(float soundeffect){
  ofPushMatrix();
  ofTranslate(-RVB.getWidth()/4,RVB.getHeight()*0.75/2,0);
  ofScale(ofVec3f(0.8));
  ofScale(ofVec3f(RVB.getHeight()/424));
  ofRotate(180,1,0,0);
  for (size_t i = 0; i < webSamples.size(); i++) {
     webSamples[i].drawSusu(soundeffect);
   }
  ofPopMatrix();
}

//Define the sort for ordering the drawing of the triangles
bool sortDescending(ofMeshFace i, ofMeshFace j)
{
    return (j.getVertex(0).y < i.getVertex(0).y);
}

//UPDATE : une seule boucle
void web::createMesh(){
  vector<ofPoint> textcoord;
  for (size_t j = 50; j < 424-50; j+=20){
    for (size_t i = 150; i < 524-150; i+=20){
          int a,b;
          a=0;
          b=0;
           if(i<=524/2){a = -ofRandom(0,5);}
          else{a =  ofRandom(0,5);}
           if(j<=424/2){b = -ofRandom(0,5);}
           else{b = ofRandom(0,5);}
          triangulation.addPoint(ofPoint(i+a,j+b,0));
          textcoord.push_back(ofPoint(215.5+(i+a)*(RVB.getWidth()*0.842/524), -82 + (b+j) * (RVB.getHeight()*1.23 / 424)));
      }
  }

  triangulation.triangulate();
  for (size_t i = 0; i < textcoord.size(); i++) {
    triangulation.triangleMesh.addTexCoord(textcoord[i]);
  }

  triangles = triangulation.triangleMesh.getUniqueFaces();
  ofSort(triangles,sortDescending); //order the triangles for the drawing

}
