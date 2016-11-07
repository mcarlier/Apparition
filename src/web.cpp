

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


  positionMesh=2;
  if(positionMesh==1){
    RVB.load("imgRight.jpg");
    RVB0.load("texRGBRight0.jpg");
    Depth.load("imgDRight.jpg");
    Depth0.load("texDepthRight0.jpg");
  }
  else{
    RVB.load("imgLeft.jpg");
    RVB0.load("texRGBLeft0.jpg");
    Depth.load("imgDLeft.jpg");
    Depth0.load("texDepthLeft0.jpg");
  }

  createMesh();


  //TMP
  x.set("x : ", -500, 0, 300);
  y.set("y : ",-500, -200, 300);
  dx.set("dx",0.0f, 0.0f, 3.0f);
  dy.set("dy",0.0f, 0.0f, 3.0f);

/*
  build a gui of sliders from three ofParameters
*/
  gui = new ofxDatGui();
  gui->addLabel("help position image2");
  gui->addSlider(x);
  gui->addSlider(y);
  gui->addSlider(dx);
  gui->addSlider(dy);
  gui->setPosition(ofGetWidth()/2 - gui->getWidth() - 20, 100);
  gui->onSliderEvent(this, &web::onSliderEvent);

/*
  create three sliders that use the same ofParameters as the gui
*/
  int xt = gui->getPosition().x + gui->getWidth() + 40;
  l1 = new ofxDatGuiLabel("help position image");
  l1->setPosition(xt, gui->getPosition().y);

  s1 = new ofxDatGuiSlider(x);
  s1->setPosition(xt, l1->getY() + l1->getHeight() + 2);
  s2 = new ofxDatGuiSlider(y);
  s2->setPosition(xt, s1->getY() + s1->getHeight() + 2);
  s3 = new ofxDatGuiSlider(dx);
  s3->setPosition(xt, s2->getY() + s2->getHeight() + 2);
  s4 = new ofxDatGuiSlider(dy);
  s4->setPosition(xt, s4->getY() + s4->getHeight() + 2);

  s1->onSliderEvent(this, &web::onSliderEvent);
  s2->onSliderEvent(this, &web::onSliderEvent);
  s3->onSliderEvent(this, &web::onSliderEvent);
}

//--------------------------------------------------------------
void web::update(){
  if(state==1){
    update_appeared();
  }
  //triangulation.triangleMesh.addTexCoord(ofVec2f(0,1000));

  //TMP
  s1->update();
  s2->update();
  s3->update();
  s4->update();

  // triangulationRight.triangleMesh.clearTexCoords();
  // for (size_t i = 0; i < Depth.getWidth(); i+=10){//=int(ofRandom(10,20))) {
  //     for (size_t j = 0; j < Depth.getHeight()-45; j+=10){//=int(ofRandom(10,20))) {
  //       if(Depth.getColor(i,j).r>200){
  //         std::cout << "x = "<< i*(RVB.getWidth()*0.65/Depth.getWidth())<< " y =  " << j  * (RVB.getHeight() / Depth.getHeight()) << std::endl;
  //         triangulationRight.triangleMesh.addTexCoord(ofPoint(x+i*(RVB.getWidth()*dx/Depth.getWidth()), y + j * (RVB.getHeight()*dy / Depth.getHeight())));
  //
  //         }
  //     }
  // }

}

void web::draw(){

  ofScale(ofVec3f(0.65));
  ofTranslate(-RVB.getWidth()/2,-RVB.getHeight()/2,0);
  RVB.draw(0,0);
  ofTranslate(RVB.getWidth()/2,RVB.getHeight()/2,0);
  ofScale(ofVec3f(1/0.65));

  //RightSide
  if(positionMesh==1){
  // ofPushMatrix();
  // ofSetColor(ofColor::white);
  // ofTranslate(0,-RVB0.getHeight()*0.75/2,0);
  // ofScale(ofVec3f(0.8));
  // ofScale(ofVec3f(RVB0.getHeight()/Depth0.getHeight()));
  // Depth.draw(0,0);
  // ofPopMatrix();

  ofPushMatrix();
  ofTranslate(0,RVB0.getHeight()*0.75/2,0);
  ofScale(ofVec3f(0.8));
  ofScale(ofVec3f(RVB0.getHeight()/Depth0.getHeight()));
  ofRotate(180,1,0,0);
  ofSetColor(ofColor::purple);
  shaderWeb.begin();

  RVB.bind();

  //plane.draw();
  triangulationRight.triangleMesh.draw();
  //meshRight.drawWireframe();
  RVB.unbind();
  shaderWeb.end();
  //meshRight.drawFaces();
  ofPopMatrix();
  }
  else{
      ofScale(ofVec3f(0.65));
    ofTranslate(-RVB.getWidth()/2,-RVB.getHeight()/2,0);
    //if(SomeoneDetected==0){
      //RVB.draw(0,0);
    ofTranslate(RVB.getWidth()/2,RVB.getHeight()/2,0);
      ofScale(ofVec3f(1/0.65));


    //LeftSide
    // ofPushMatrix();
    // ofSetColor(ofColor::white);
    // ofTranslate(-Depth.getWidth()*1.65,-RVB0.getHeight()*0.65/2,0);
    // ofScale(ofVec3f(0.65));
    // ofScale(ofVec3f(RVB0.getHeight()/Depth0.getHeight()));
    // //Depth.draw(0,0);
    // ofPopMatrix();

    ofPushMatrix();
    ofTranslate(-Depth.getWidth()*1.9,RVB0.getHeight()*0.75/2,0);
    ofScale(ofVec3f(0.8));
    ofScale(ofVec3f(RVB0.getHeight()/Depth0.getHeight()));
    ofRotate(180,1,0,0);
    ofSetColor(ofColor::purple);
    shaderWeb.begin();
    RVB.bind();
    triangulationRight.triangleMesh.draw();
    RVB.unbind();
    shaderWeb.end();
    ofPopMatrix();
    }





  //RVB0.draw(-RVB.getWidth()/2,-RVB.getHeight()/2);
  ofScale(ofVec3f(2));

  //Light
  shaderSusu.setUniform3f("iResolution", 1024,768,400);
  shaderSusu.setUniform1f("iGlobalTime", ofGetElapsedTimef());

  //TMP
  l1->draw();
  s1->draw();
  s2->draw();
  s3->draw();
  s4->draw();

}

// a optimiser en une seule boucle
void web::createMesh(){
  for (size_t i = 0; i < Depth.getWidth(); i+=10){//int(ofRandom(10,20))) {
      for (size_t j = 0; j < Depth.getHeight()-45; j+=10){//int(ofRandom(10,20))) {
        if(Depth.getColor(i,j).r>200){
          // meshRight.addVertex(ofVec3f(i,j,0));
          // meshRight.addTexCoord(ofPoint(i*(RVB.getWidth()/Depth.getWidth()), j * (RVB.getHeight() / Depth.getHeight())));
          // meshRight.setupIndicesAuto();
          triangulationRight.addPoint(ofPoint(i,j,0));
          }
      }
  }
  triangulationRight.triangulate();
  for (size_t i = 0; i < Depth.getWidth(); i+=10){//=int(ofRandom(10,20))) {
      for (size_t j = 0; j < Depth.getHeight()-45; j+=10){//=int(ofRandom(10,20))) {
        if(Depth.getColor(i,j).r>200){
          std::cout << "x = "<< i*(RVB.getWidth()*0.65/Depth.getWidth())<< " y =  " << j  * (RVB.getHeight() / Depth.getHeight()) << std::endl;
          if(positionMesh==1){
          triangulationRight.triangleMesh.addTexCoord(ofPoint(959+i*(RVB.getWidth()*0.42/Depth.getWidth()), -82 + j * (RVB.getHeight()*1.23 / Depth.getHeight())));
          }
          else{
          triangulationRight.triangleMesh.addTexCoord(ofPoint(209+i*(RVB.getWidth()*0.42/Depth.getWidth()), -85 + j * (RVB.getHeight()*1.23 / Depth.getHeight())));
          }

          }
      }
  }

}

void web::changeState(){
  state++;
  if(state==1){
    setup_appeared();
  }
}


//TPM
void web::onSliderEvent(ofxDatGuiSliderEvent e)
{
    cout << e.target->getName() << " : " << e.value << endl;
}
