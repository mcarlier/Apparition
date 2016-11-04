#include "web.h"
int essai = 0;
void web::setup(){
  state = 0;
  mesh.load("lofi-bunny.ply");
  NumWebSample = int(ofRandom(1,6));

  ofLoadImage(texture, "img.jpg");
  shaderSusu.load("shaders/shaderNoise");
  //img.load("img.jpg");
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
  plane.mapTexCoords(0, 0, texture.getWidth(), texture.getHeight());

  vboSusu.setVertexData(&pointsSusu[0], (int)pointsSusu.size(), GL_STATIC_DRAW);
  vboSusu.setNormalData(&sizesSusu[0], (int)pointsSusu.size(), GL_STATIC_DRAW);
  shaderWeb.load("shaders/shader");


  RVB.load("imgRight.jpg");
  RVB0.load("texRGBRight0.jpg");
  Depth.load("imgDRight.jpg");
  Depth0.load("texDepthRight0.jpg");
  createMesh();
}

//--------------------------------------------------------------
void web::update(){
  if(state==1){
    update_appeared();
  }
  triangulation.triangleMesh.addTexCoord(ofVec2f(0,1000));

}
void web::createMesh(){
  int colorclair = 0;
  for (size_t i = 0; i < Depth.getPixels().size(); i+=100) {
    if(Depth.getColor(i).r>colorclair){
      colorclair = Depth.getColor(i).r;
    }
  }
  std::cout <<colorclair<< std::endl;

  for (size_t i = 0; i < Depth.getWidth(); i+=int(ofRandom(10,20))) {
      for (size_t j = 0; j < Depth.getHeight(); j+=int(ofRandom(10,20))) {
        if(Depth.getColor(i,j).r>200){
          std::cout << "addvertex" << std::endl;
          meshRight.addVertex(ofVec3f(i,j,0));
          }
        // else{
        //   Depth.setColor(i, ofColor(0,0,0));
        //
        //   //Depth.setColor(i, ofColor(255,255,255));
        // }
      }
    // std::cout << i << std::endl;
    // std::cout << Depth.getColor(i) << std::endl;
    // Depth.setColor(i,ofColor(0,0,0,255));//Depth0.getColor(i));
    // std::cout << Depth.getColor(i) << std::endl;
  }
  for (int i = 0; i < meshRight.getNumVertices(); i++) {
    triangulationRight.addPoint(ofPoint(meshRight.getVertex(i)));
  }
  triangulationRight.triangulate();
}
void web::draw(){

  //RightSide
  ofPushMatrix();
  ofSetColor(ofColor::white);
  ofTranslate(0,-RVB0.getHeight()*0.65/2,0);
  ofScale(ofVec3f(0.65));
  ofScale(ofVec3f(RVB0.getHeight()/Depth0.getHeight()));
  //Depth.draw(0,0);
  ofPopMatrix();

  ofPushMatrix();
  ofTranslate(0,RVB0.getHeight()*0.65/2,0);
  ofScale(ofVec3f(0.65));
  ofScale(ofVec3f(RVB0.getHeight()/Depth0.getHeight()));
  ofRotate(180,1,0,0);
  ofSetColor(ofColor::purple);
  triangulationRight.triangleMesh.drawWireframe();
  meshRight.drawFaces();
  ofPopMatrix();
  //LeftSide



  //RVB0.draw(-RVB.getWidth()/2,-RVB.getHeight()/2);
  ofScale(ofVec3f(2));

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
  //img.getTexture().bind();

  // texture.bind();
  // shaderSusu.begin();
  // RVB.draw(0,0);
  //
  // vboSusu.draw(GL_POINTS, 0, (int)pointsSusu.size());
  // //plane.draw();
  // for (size_t i = 0; i < webSamples.size(); i++) {
  //
  //   // shaderWeb.setUniform4f("uColor",essai,essai,essai,essai);
  //   //
  //    //triangulation.triangleMesh.draw();
  //   //
  //
  //   //mesh.draw();
  //   //triangulation.triangleMesh.draw();
  //   webSamples[i].drawSusu();
  //   //webSamples[i].mesh.addTexCoord(ofVec2f(0,10000));
  //   webSamples[i].mesh.drawWireframe();
  //   //webSamples[i].mesh.draw();
  //
  //   // //webSamples[i].drawSusu();
  //   //   if(state == 1)
  //    webSamples[i].drawCurrentPath_appeared();
  //
  // }
  //
  // shaderSusu.end();
  // texture.unbind();
  //img.getTexture().unbind();
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

//shaderWeb.begin();

//mkshaderWeb.setGeometryInputType(GL_POINTS);
//shaderWeb.setUniform1f("time2", ofGetElapsedTimef());



//shaderWeb.end();

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
