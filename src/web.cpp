#include "web.h"

void web::setup(){
  state = 0;
  mesh.load("lofi-bunny.ply");
  NumWebSample = int(ofRandom(1,6));

  ofDisableArbTex();
  ofLoadImage(texture, "dot.png");
  shaderSusu.load("shaders/shader");

  for (size_t i = 0; i < NumWebSample; i++) {
    webSample su;
    su.setup();
    webSamples.push_back(su);
    float size = ofRandom(5, 50);
  	sizesSusu.push_back(ofVec3f(size));
    pointsSusu.push_back(webSamples[i].position);
  }

  vboSusu.setVertexData(&pointsSusu[0], (int)pointsSusu.size(), GL_STATIC_DRAW);
  vboSusu.setNormalData(&sizesSusu[0], (int)pointsSusu.size(), GL_STATIC_DRAW);

}

//--------------------------------------------------------------
void web::update(){
  if(state==1){
    update_appeared();
  }
}

void web::draw(){
  glDepthMask(GL_FALSE);
  ofSetColor(255, 100, 90);
  ofEnableBlendMode(OF_BLENDMODE_ADD);
  ofEnablePointSprites();
  shaderSusu.begin();
  texture.bind();
  //vboSusu.draw(GL_POINTS, 0, (int)pointsSusu.size());
  texture.unbind();
  shaderSusu.end();
  ofDisablePointSprites();
  ofDisableBlendMode();


  for (size_t i = 0; i < webSamples.size(); i++) {
    webSamples[i].drawWeb();
    webSamples[i].drawSusu();
      if(state == 1){}
    webSamples[i].drawCurrentPath_appeared();

  }
  ofNoFill();
  //triangulation.draw();
  //mesh.drawWireframe();

}

void web::changeState(){
  state++;
  if(state==1){
    setup_appeared();
  }
}
