#include "web.h"
int essai = 0;
void web::setup(){
  state = 0;
  mesh.load("lofi-bunny.ply");
  NumWebSample = int(ofRandom(1,6));

  ofDisableArbTex();
  //ofLoadImage(texture, "images.jpg");
  shaderSusu.load("shaders/shader");
  img.load("dot2.png");
  //shaderSusu.setUniformTexture("texture", texture.getTextureReference(), 1 );

  for (size_t i = 0; i < NumWebSample; i++) {
    webSample su;
    su.setup();
    webSamples.push_back(su);
    float size = ofRandom(5, 50);
  	sizesSusu.push_back(ofVec3f(size));
    pointsSusu.push_back(webSamples[i].position);
  }

  plane.set(800, 600, 10, 10);
  plane.mapTexCoords(0, 0, img.getWidth(), img.getHeight());

  vboSusu.setVertexData(&pointsSusu[0], (int)pointsSusu.size(), GL_STATIC_DRAW);
  vboSusu.setNormalData(&sizesSusu[0], (int)pointsSusu.size(), GL_STATIC_DRAW);
  shaderWeb.load("shaders/shader");

}

//--------------------------------------------------------------
void web::update(){
  if(state==1){
    update_appeared();
  }
}

void web::draw(){

  //Light
  shaderSusu.setUniform3f("iResolution", 1024,768,400);
  shaderSusu.setUniform1f("iGlobalTime", ofGetElapsedTimef());

  //Neon shader
   shaderWeb.setUniform3f("iResolution", 1024,768,400);
   shaderWeb.setUniform1f("iGlobalTime", ofGetElapsedTimef());



  // glDepthMask(GL_FALSE);
  // ofSetColor(4, 30, 124);
  // ofEnableBlendMode(OF_BLENDMODE_ADD);
  // ofEnablePointSprites();

  // for (size_t i = 0; i < webSamples.size(); i++) {
  //    webSamples[i].drawSusu();
  //     webSamples[i].mesh.draw();
  // }
  //texture.bind();
  img.getTexture().bind();
  shaderSusu.begin();
  vboSusu.draw(GL_POINTS, 0, (int)pointsSusu.size());
  //plane.draw();
  shaderSusu.end();
  img.getTexture().unbind();
  //triangulation.triangleMesh.draw();
  // mesh.draw();
  //vboSusu.draw(GL_POINTS, 0, (int)pointsSusu.size());
//  tex0.draw(pointsSusu[0].x,pointsSusu[0].y,pointsSusu[0].z);
  // triangulation.triangleMesh.draw();
  //
  // for (size_t i = 0; i < webSamples.size(); i++) {
  //    webSamples[i].mesh.draw();
  //    //webSamples[i].mesh.mapTexCoords(texture);
  //   webSamples[i].drawSusu();
  //     if(state == 1){}
  //   webSamples[i].drawCurrentPath_appeared();
  //
  // }

  //texture.unbind();


  // ofDisablePointSprites();
  // ofDisableBlendMode();

// float percentX = mouseX / (float)ofGetWidth();
// percentX = ofClamp(percentX, 0, 1);

// the mouse/touch X position changes the color of the plane.
// please have a look inside the frag shader,
// we are using the globalColor value that OF passes into the shader everytime you call ofSetColor().
// ofColor colorLeft = ofColor::magenta;
// ofColor colorRight = ofColor::cyan;
// ofColor colorMix = colorLeft.getLerped(colorRight, percentX);
//ofSetColor(colorMix);

shaderWeb.begin();

//mkshaderWeb.setGeometryInputType(GL_POINTS);
//shaderWeb.setUniform1f("time2", ofGetElapsedTimef());


for (size_t i = 0; i < webSamples.size(); i++) {

  // shaderWeb.setUniform4f("uColor",essai,essai,essai,essai);
  //
   //triangulation.triangleMesh.draw();
  //

//  mesh.draw();
  //triangulation.triangleMesh.draw();
  webSamples[i].drawSusu();
  webSamples[i].mesh.drawWireframe();
  // //webSamples[i].drawSusu();
  //   if(state == 1)
   webSamples[i].drawCurrentPath_appeared();

}

shaderWeb.end();

  //shaderWeb.begin();
  //vboWeb.draw(GL_POINTS, 0, mesh.getUniqueFaces().size());
  //shaderWeb.end();



  // ofNoFill();
  //triangulation.draw();
  //mesh.drawWireframe();

}

void web::changeState(){
  state++;
  if(state==1){
    setup_appeared();
  }
}
