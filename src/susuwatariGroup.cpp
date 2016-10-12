#include "susuwatariGroup.h"

int susuwatariGroup::setup(int NumSusuwatari,vector<ofMeshFace> triangles,int triangleDrawn){
  ofDisableArbTex();
  ofLoadImage(texture, "dot.png");

  for (size_t i = 0; i < NumSusuwatari; i++) {
    susuwatari su;
    su.setup(triangles[triangleDrawn]);
    triangleDrawn ++;
    susuwataris.push_back(su);
    addPoint(susuwataris[i].position.x, susuwataris[i].position.y, susuwataris[i].position.z);
  }
    shaderSusu.load("shaders/shader");
    int total = (int)pointsSusu.size();
    vboSusu.setVertexData(&pointsSusu[0], total, GL_STATIC_DRAW);
    //vboSusu.setNormalData(&sizesSusu[0], total, GL_STATIC_DRAW);

    return triangleDrawn;
}

int susuwatariGroup::update(vector<ofMeshFace> triangles,int totalTriangle, int triangleDrawn){
  for (size_t i = 0; i < susuwataris.size(); i++) {
    if( susuwataris[i].state == 0 && triangleDrawn < totalTriangle){
      susuwataris[i].addTriangle(triangles[triangleDrawn]);
      triangleDrawn ++;
    }
    susuwataris[i].update();
    pointsSusu[i]=susuwataris[i].position;
  }
  vboSusu.updateVertexData(&pointsSusu[0],(int)pointsSusu.size());
  return triangleDrawn;
}
void susuwatariGroup::draw(){

  glDepthMask(GL_FALSE);
  ofSetColor(255, 100, 90);
  ofEnableBlendMode(OF_BLENDMODE_ADD);
  ofEnablePointSprites();
  shaderSusu.begin();
  texture.bind();
  vboSusu.draw(GL_POINTS, 0, (int)pointsSusu.size());
  texture.unbind();
  shaderSusu.end();
  ofDisablePointSprites();
  ofDisableBlendMode();

  ofSetColor(ofColor::blue);
  // for (size_t i = 0; i < susuwataris.size(); i++) {
  //   susuwataris[i].drawSusu();
  // }
  for (size_t i = 0; i < susuwataris.size(); i++) {
    susuwataris[i].drawWeb();
  }

}

void susuwatariGroup::addPoint(float x, float y, float z) {
	ofVec3f p(x, y, z);
	pointsSusu.push_back(p);

	// we are passing the size in as a normal x position
	float size = ofRandom(5, 50);
	sizesSusu.push_back(ofVec3f(size));
}
