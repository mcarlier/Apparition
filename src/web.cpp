#include "web.h"
//Main setup function
void web::setup(Json::Value jsoninfos,int lastuserID){
  NumWebSample = stoi(jsoninfos["NumWebSample"].asString());
  webSample::speedApparition=stof(jsoninfos["webSamples"]["speedApparition"].asString());
  webSample::speedEnd=stof(jsoninfos["webSamples"]["speedDisparition"].asString());
  webSample::speedFadeIn=stoi(jsoninfos["webSamples"]["timerappearance"].asString());
  webSample::speedFadeOut=stoi(jsoninfos["webSamples"]["timerDesapearance"].asString());
  for (size_t i = 0; i < NumWebSample; i++) {
    webSample su;
    su.setup();
    webSamples.push_back(su);
  }

  changeState(0);
  shaderEnd.load("shaders/end");
  meshDesappear = false;
  Desappeare.load("shaders/desappeare");
  int lastuserIDint = (lastuserID-1)%5;
  RVB.load("img"+to_string(lastuserIDint)+".jpg");
  createMesh();
  meshcomplete = false;

  timerMeshDesappeare.setup(stoi(jsoninfos["timerMeshDesappeare"].asString()));//Time mesh desappeare (movement)
  end = false;
  waitPeopleToGo = false;
  setupWaitPeopleToGo =false;
  gui.setup(); //Update : no need
  gui.add(a.setup("a", 0.2, 0, 1));
  gui.add(b.setup("b", 0.5, 0, 1));
  gui.add(c.setup("c", 0.5, 0, 1));
  gui.add(d.setup("d", 0.8, 0, 1));

  multipleFade::numberOfImages=stoi(jsoninfos["multifade"]["numberOfImages"].asString());
  multipleFade.setup(lastuserID,triangulation.triangleMesh,jsoninfos["multifade"]);

}
//Set up the end = when the mesh is complete
void web::setupEnd(){
  std::cout << "endSetup" << '\n';
  end = true;
  triangleDrawn=triangulation.getNumTriangles()-1;
  for (size_t i = 0; i < webSamples.size(); i++) {
    webSamples[i].end=true;
    webSamples[i].speed=ofRandom(webSamples[i].speedEnd-2,webSamples[i].speedEnd);
    webSamples[i].changeState(2);
  }
}

//Main update fonction
void web::update(){
  if(end==true){
    updateEnd();
  }
  else{
    for (size_t i = 0; i < webSamples.size(); i++) {
      webSamples[i].updatefaces();
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
// update fonction end =  when the mesh is complete
void web::updateEnd(){
  int count=0;
  int total=0;
  for (size_t i = 0; i < webSamples.size(); i++) {
      webSamples[i].updatefaces();
      if( webSamples[i].state_appeared == 0 &&triangleDrawn>=0){
        webSamples[i].addTriangle_appeared(triangles[triangleDrawn]);
        triangleDrawn--;
      }
      else if (webSamples[i].state_appeared == 0 && triangleDrawn < 0){
        ofMeshFace t;
        webSamples[i].addTriangle_appeared(t);
        webSamples[i].speed = webSamples[i].speedApparition;
        webSamples[i].changeState(1);
        webSamples[i].end = false;
      }

      webSamples[i].update();
      total++;
      count++;
      if (webSamples[i].end==false){
        for (size_t j = 0; j < webSamples[i].faces.size() ; j++) {
          total++;
          if(webSamples[i].faces[i].timerappearance.getNormalizedProgress()<0.1){
            count++;
          }
        }
      }

    }
    if (count>webSamples.size()&&count==total&&!multipleFade.started){
      std::cout << "begin fade multiple" << '\n';
      multipleFade.start();
      changeState(1);
    }
    if(multipleFade.started&&!multipleFade.isRunning){
      std::cout << "Please go" << '\n';
      end=false;
      waitPeopleToGo=true;
      multipleFade.started=false;
    }
    if(multipleFade.started){
      multipleFade.update();
    }
}

//main Draw function
void web::draw(ofShader shader,ofShader shaderweb,float soundeffect,float currentTime){
    ofSetColor(ofColor(255,255,255,100));
    if(!multipleFade.needToSeeBg){
      draw_web(shaderweb,currentTime);
    }
    if(multipleFade.started){
      multipleFade.draw(Desappeare,currentTime);
    }
    drawSusus(shader,soundeffect,currentTime);
}
//Draw the Susu =  white balls
void web::drawSusus(ofShader shader,float soundeffect,float currentTime){
  ofPushMatrix();
  ofTranslate(-RVB.getWidth()/4,RVB.getHeight()*0.75/2,0);
  ofScale(ofVec3f(0.8));
  ofScale(ofVec3f(RVB.getHeight()/424));
  ofRotate(180,1,0,0);
  for (size_t i = 0; i < webSamples.size(); i++) {
     webSamples[i].drawSusu(shader,soundeffect,currentTime);
   }
  ofPopMatrix();
}
//Draw the web = mesh
void web::draw_web(ofShader shader,float currentTime){
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
    sh.setUniform1f("u_time", currentTime);
    sh.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
    sh.setUniform1f("timer", timerMeshDesappeare.getNormalizedProgress());
    sh.setUniform1f("a", a);
    sh.setUniform1f("b", b);
    sh.setUniform1f("c", c);
    sh.setUniform1f("d", d);
    RVB.bind();
    if(!waitPeopleToGo) {
        for (size_t i = 0; i < webSamples.size(); i++) {
           webSamples[i].mesh.draw();
         }
         RVB.unbind();
         sh.end();
    }
    draw_fadetriangles(currentTime);
    if (end) {
      sh.begin();
      base.bind();
      for (size_t i = 0; i < webSamples.size(); i++) {
        webSamples[i].meshEnd.draw();
      }
      base.unbind();
      sh.end();

    }

    ofPopMatrix();

}
//Draw the fade triangles, the part of the mesh that are fade in/out
void web::draw_fadetriangles(float currentTime){
  ofShader sh2;
  if(meshDesappear){
      sh2 = Desappeare;
  }
  else{
    sh2 = shaderEnd;
  }
   sh2.begin();
   RVB.bind();
   sh2.setUniform1f("u_time", currentTime);
   sh2.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
   for (size_t i = 0; i < webSamples.size(); i++) {
     for (size_t j = 0; j < webSamples[i].faces.size(); j++) {
       if(!meshDesappear){
         sh2.setUniform1f("timer", webSamples[i].faces[j].timerappearance.getNormalizedProgress());
       }
       else{
         if(webSamples[i].faces[j].timerappearance.getNormalizedProgress()>=0.1){
           sh2.setUniform1f("timer", 1-webSamples[i].faces[j].timerappearance.getNormalizedProgress()+timerMeshDesappeare.getNormalizedProgress());
         }
         else{
           sh2.setUniform1f("timer", timerMeshDesappeare.getNormalizedProgress());
         }
       }
       if((webSamples[i].faces[j].canDraw)&&(webSamples[i].faces[j].type==1)){
         webSamples[i].faces[j].lastFace.draw();
       }
     }
   }
   RVB.unbind();
   sh2.end();
   if(end){
     shaderEnd.begin();
     base.bind();
     shaderEnd.setUniform1f("u_time", currentTime);
     shaderEnd.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
     for (size_t i = 0; i < webSamples.size(); i++) {
       for (size_t j = 0; j < webSamples[i].faces.size(); j++) {
         shaderEnd.setUniform1f("timer", webSamples[i].faces[j].timerappearance.getNormalizedProgress());
         if((webSamples[i].faces[j].canDraw)&&(webSamples[i].faces[j].type==2)){
           webSamples[i].faces[j].lastFace.draw();
         }
       }
     }
     base.unbind();
     shaderEnd.end();
   }
  }

//Change the state of the web. 0 = rest,1 =someone detected 2 = drawing;
void web::changeState(int newState){
  triangleDrawn = 0;
  for (size_t i = 0; i < webSamples.size(); i++) {
    webSamples[i].changeState(newState);
  }
  if((state==2)&&!waitPeopleToGo&&!multipleFade.started){
    std::cout << "disappear meash" << '\n';
      meshDesappear = true;
      timerMeshDesappeare.start(false);
  }
  state = newState;
}
//Create the mesh that will be draw.
void web::createMesh(){
  ofxDelaunay trtr;
  vector<ofMeshFace> teee;
  vector<ofPoint> textcoord;
  for (size_t j = 50; j < 424-50; j+=20){
    for (size_t i = 150; i < 524-150; i+=20){
          int a,b;
          a=0;
          b=0;

           if((i<=524/2)&&(i!=150)){a = -ofRandom(0,5);}
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
//Increase the speed of the susu when they draw the top of the mesh
void web::increaseSpeed(){
  if (triangleDrawn>=triangulation.getNumTriangles()*5/6) {
      for (size_t i = 0; i < webSamples.size(); i++) {
        if (webSamples[i].speed<webSamples[i].speedEnd) {
            webSamples[i].speed+=0.01;
        }
    }
  }

}
//Check if the desappearance of the mesh is complete and then erase the datas.
void web::makeMeshDesappeare(){
   timerMeshDesappeare.update();
   if(!timerMeshDesappeare.bIsRunning){
     meshDesappear = false;
     for (size_t i = 0; i < webSamples.size(); i++) {
       webSamples[i].clear();
       webSamples[i].faces.erase(webSamples[i].faces.begin(),webSamples[i].faces.begin()+webSamples[i].faces.size());
     }
   }
 }

//reinitialise all the datas fo the next user.
void web::startAnew(ofImage newImg){
  for (size_t i = 0; i < webSamples.size(); i++) {
      webSamples[i].clear();
      changeState(0);
      webSamples[i].meshEnd.clear();
      webSamples[i].speed = ofRandom(webSamples[i].speedApparition-2,webSamples[i].speedApparition);
      webSamples[i].end = false;
      meshDesappear = false;
      RVB = newImg;
      meshcomplete = false;
      end = false;
      waitPeopleToGo = false;
      setupWaitPeopleToGo = false;
      multipleFade.startAnew(newImg);
  }
}


//Define the sort for ordering the drawing of the triangles (used in createMesh())
bool sortDescending(ofMeshFace i, ofMeshFace j)
{
    return (j.getVertex(0).y < i.getVertex(0).y);
}
