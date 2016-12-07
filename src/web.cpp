#include "web.h"
int essai = 0;
void web::setup(){

  NumWebSample = 10;
  for (size_t i = 0; i < NumWebSample; i++) {
    webSample su;
    su.setup();
    webSamples.push_back(su);
  }
  changeState(0);
  shaderWeb.load("shaders/desappeare2");
  shaderEnd.load("shaders/end");

  meshDesappear = false;
  Desappeare.load("shaders/desappeare");

  RVB.load("img.jpg");
  createMesh();
  meshcomplete = false;

  timerMeshDesappeare.setup(2000);
  end = false;
  waitPeopleToGo = false;



}

//--------------------------------------------------------------
void web::update(){
  if(end==true){
    updateEnd();
  }
  else{
    for (size_t i = 0; i < webSamples.size(); i++) {
      if (webSamples[i].state==2) {
        if( webSamples[i].state_appeared == 0 && triangleDrawn < triangulation.getNumTriangles()){
          webSamples[i].addTriangle_appeared(triangles[triangleDrawn]);
          triangleDrawn ++;
        }
        else if ( webSamples[i].state_appeared == 0 && triangleDrawn >= triangulation.getNumTriangles()){
          meshcomplete = true;
        }
      }
      webSamples[i].update();
      increaseSpeed();
    }
    if(meshcomplete&&!waitPeopleToGo){
      setupEnd();
    }
  }
  if (meshDesappear==true){
    makeMeshDesappeare();
  }
}
void web::updateEnd(){
  int count=0;
  for (size_t i = 0; i < webSamples.size(); i++) {
      if( webSamples[i].state_appeared == 0 &&triangleDrawn>=0){
        webSamples[i].addTriangle_appeared(triangles[triangleDrawn]);
        triangleDrawn--;
      }
      else if ( webSamples[i].state_appeared == 0 && triangleDrawn < 0){
        ofMeshFace t;
        webSamples[i].addTriangle_appeared(t);
        webSamples[i].speed = 6;
        //webSamples[i].changeState(1);
        webSamples[i].end = false;
      }

      webSamples[i].update();
      if (webSamples[i].end==false) {
        count++;
        end=true;
        //webSamples[i].changeState(0);
      }

    }
    if (count==webSamples.size()){
      std::cout << "please go" << '\n';
      end=false;
      waitPeopleToGo=true;
      changeState(1);
    }
}
void web::draw(ofShader shader,float soundeffect){
    ofSetColor(ofColor(255,255,255,100));
    draw_web(shader);
    drawSusus(shader,soundeffect);
}
void web::changeState(int newState){
  triangleDrawn = 0;
  for (size_t i = 0; i < webSamples.size(); i++) {
    webSamples[i].changeState(newState);
  }
  if((state==2)&&!waitPeopleToGo){
    std::cout << "disappear meash" << '\n';
      meshDesappear = true;
      timerMeshDesappeare.start(false);
  }
  state = newState;

}

void web::setupEnd(){
  std::cout << "endSetup" << '\n';
  end = true;
  triangleDrawn=triangulation.getNumTriangles()-1;
  for (size_t i = 0; i < webSamples.size(); i++) {
    webSamples[i].end=true;
    webSamples[i].speed=10;
    webSamples[i].changeState(2);
  }

}

void web::increaseSpeed(){
  if (triangleDrawn>=triangulation.getNumTriangles()*5/6) {
      for (size_t i = 0; i < webSamples.size(); i++) {
        if (webSamples[i].speed<10) {
            webSamples[i].speed+=0.01;
        }
    }
  }

}

void web::startAnew(ofImage newImg){
  for (size_t i = 0; i < webSamples.size(); i++) {
      webSamples[i].clear();
      changeState(0);
      webSamples[i].meshEnd.clear();
      webSamples[i].speed = 6;
      webSamples[i].end = false;
      meshDesappear = false;
      RVB = newImg;
      meshcomplete = false;
      end = false;
      waitPeopleToGo = false;
  }
}

void web::makeMeshDesappeare(){
   timerMeshDesappeare.update();
   if(!timerMeshDesappeare.bIsRunning){
     meshDesappear = false;
     std::cout << "ici" << '\n';
     for (size_t i = 0; i < webSamples.size(); i++) {
       webSamples[i].clear();
     }
     ofShader temp;
     temp = shaderWeb;
     shaderWeb = Desappeare;
     Desappeare = temp;
   }
 }

void web::draw_web(ofShader shader){
    ofShader sh;
    if(meshDesappear){
        sh = Desappeare;
    }
    else{
      sh = shader;
    }
    ofPushMatrix();
    ofTranslate(-RVB.getWidth()/4,RVB.getHeight()*0.75/2,0);
    ofScale(ofVec3f(0.8));
    ofScale(ofVec3f(RVB.getHeight()/424));
    ofRotate(180,1,0,0);
    ofSetColor(ofColor::white);


    sh.begin();
    sh.setUniform1f("u_time", ofGetElapsedTimef());
    sh.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
    sh.setUniform1f("timer", timerMeshDesappeare.getNormalizedProgress());
    std::cout << timerMeshDesappeare.getNormalizedProgress() << '\n';

    RVB.bind();
    if(!waitPeopleToGo) {
      if (meshcomplete) {
        triangulation.triangleMesh.draw();
      }
      else{
        for (size_t i = 0; i < webSamples.size(); i++) {
           webSamples[i].mesh.draw();
         }
      }
    }
    RVB.unbind();
    if (end) {
      base.bind();
      for (size_t i = 0; i < webSamples.size(); i++) {
        webSamples[i].meshEnd.draw();
      }
      base.unbind();
    }
    sh.end();
    ofPopMatrix();
}

void web::drawSusus(ofShader shader,float soundeffect){
  ofPushMatrix();
  ofTranslate(-RVB.getWidth()/4,RVB.getHeight()*0.75/2,0);
  ofScale(ofVec3f(0.8));
  ofScale(ofVec3f(RVB.getHeight()/424));
  ofRotate(180,1,0,0);
  for (size_t i = 0; i < webSamples.size(); i++) {
     webSamples[i].drawSusu(shader,soundeffect);
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
  ofxDelaunay trtr;
  vector<ofMeshFace> teee;
  vector<ofPoint> textcoord;
  for (size_t j = 50; j < 424-50; j+=20){
    for (size_t i = 150; i < 524-150; i+=20){
          int a,b;
          a=0;
          b=0;

           if(i<=524/2){a = -ofRandom(0,5);}
          else{a =  ofRandom(0,5);}

           if(j<=(424-50)/2){b = -ofRandom(0,5);}
           else if (j<334){b = ofRandom(0,5);}

          triangulation.addPoint(ofPoint(i+a,j+b,0));
          textcoord.push_back(ofPoint(221.8+(i+a)*(RVB.getWidth()*0.855/524), -84.15 + (b+j) * (RVB.getHeight()*1.2325 / 424)));
      }
  }

  triangulation.triangulate();
  for (size_t i = 0; i < textcoord.size(); i++) {
    triangulation.triangleMesh.addTexCoord(textcoord[i]);
  }

  triangles = triangulation.triangleMesh.getUniqueFaces();
  ofSort(triangles,sortDescending); //order the triangles for the drawing

}
