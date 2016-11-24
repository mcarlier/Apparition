#include "web.h"

void web::setup_appeared(){
  triangleDrawn = 0;
  for (size_t i = 0; i < webSamples.size(); i++) {
    webSamples[i].setup_appeared(triangles[triangleDrawn]);
    triangleDrawn ++;
  }
}

void web::update_appeared(){
  for (size_t i = 0; i < webSamples.size(); i++) {
    if( webSamples[i].state_appeared == 0 && triangleDrawn <= triangulation.getNumTriangles()){
      webSamples[i].addTriangle_appeared(triangles[triangleDrawn]);
      triangleDrawn ++;
    }
    webSamples[i].update_appeared();
  }
}

void web::draw_appeard(){
  //RightSide
  if(positionMesh==1){
    ofPushMatrix();
    ofTranslate(0,RVB.getHeight()*0.75/2,0);
    ofScale(ofVec3f(0.8));
    ofScale(ofVec3f(RVB.getHeight()/Depth.getHeight()));
    ofRotate(180,1,0,0);
    ofSetColor(ofColor::white);
    shaderWeb.begin();
    shaderWeb.setUniform1f("u_time", ofGetElapsedTimef());
    shaderWeb.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
    RVB.bind();
    //triangulation.triangleMesh.draw();
    for (size_t i = 0; i < webSamples.size(); i++) {
       webSamples[i].mesh.draw();
    }
    RVB.unbind();
    shaderWeb.end();
    //shaderSusu.begin();
    //shaderSusu.setUniform1f("u_time", ofGetElapsedTimef());
    //shaderSusu.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
    for (size_t i = 0; i < webSamples.size(); i++) {
       webSamples[i].drawSusu();

     }
    //shaderSusu.end();
    ofPopMatrix();


  }
  else{

    ofPushMatrix();
    ofTranslate(-Depth.getWidth()*1.9,RVB.getHeight()*0.75/2,0);
    ofScale(ofVec3f(0.8));
    ofScale(ofVec3f(RVB.getHeight()/Depth.getHeight()));
    ofRotate(180,1,0,0);
    ofSetColor(ofColor::purple);
    shaderWeb.begin();
    RVB.bind();
    for (size_t i = 0; i < webSamples.size(); i++) {
       webSamples[i].mesh.draw();
    }
    RVB.unbind();
    shaderWeb.end();
    for (size_t i = 0; i < webSamples.size(); i++) {
       webSamples[i].drawSusu();  }
    ofPopMatrix();
    shaderWeb.end();
    ofPopMatrix();
    }
}
