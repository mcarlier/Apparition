#include "web.h"
ITRIANGLE triang;
int triangleDrawnWireframe;
vector<ofMeshFace> trianglesMesh;
ofVec3f essai;
void web::setup(){
  mesh.load("lofi-bunny.ply");
  // load the texure


  triangleDrawnWireframe = 0;
  triangleDrawn = 0;
  rotation = 0;

  for (int i = 0; i < mesh.getNumVertices(); i++) {
    triangulation.addPoint(ofPoint(mesh.getVertex(i)));
  }
  triangulation.triangulate();
  triangles = triangulation.triangleMesh.getUniqueFaces();
  std::cout <<triangleDrawn<< std::endl;
  triangleDrawn = susuwataris.setup(4,triangles,triangleDrawn);
  std::cout <<triangleDrawn<< std::endl;

}

//--------------------------------------------------------------
void web::update(){
  triangleDrawn = susuwataris.update(triangles,triangulation.getNumTriangles(),triangleDrawn);
}

void web::draw(){
  ofRotate(rotation,0,1,0);
  susuwataris.draw();
  ofNoFill();
  //triangulation.draw();
  //mesh.drawWireframe();
  ofRotate(-rotation,0,1,0);
  rotation+=0.05;

}
