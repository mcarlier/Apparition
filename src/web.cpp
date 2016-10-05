#include "web.h"
ITRIANGLE triang;
void web::setup(){
  ofMesh mesh;
  mesh.load("lofi-bunny.ply");
  triangleDrawn = 0;
  //calcNormals();

  for (int i = 0; i < 10; i++) {
    triangulation.addPoint(ofPoint(mesh.getVertex(i)));
  }
  // triangulation.addPoint(ofPoint(0,100));
  // triangulation.addPoint(ofPoint(100,100));
  // triangulation.addPoint(ofPoint(0,0));
  // triangulation.addPoint(ofPoint(200,100));
  // triangulation.addPoint(ofPoint(200,200));
  // triangulation.addPoint(ofPoint(200,0));
   triangulation.triangulate();
  susu.setup(triangulation.getPointsForITriangle(triangulation.getTriangleAtIndex(triangleDrawn)));
  triangleDrawn++;



}

//--------------------------------------------------------------
void web::update(){
  //std::cout << triangulation.getNumTriangles()<< std::endl;

  if( susu.state == 0 && triangleDrawn < triangulation.getNumTriangles()){
    std::cout << "Change triangle" << std::endl;
    susu.addTriangle(triangulation.getPointsForITriangle(triangulation.getTriangleAtIndex(triangleDrawn)));
    triangleDrawn ++;
  }
  susu.update();
//   triang =;
//
// vector<ofPoint> points =
//    std::cout << triang.p1 << std::endl;
//    std::cout << triang.p2 << std::endl;
//    std::cout << triang.p3 << std::endl;
//
//
//    for (int i = 0; i < points.size(); i++) {
//      std::cout <<  points[i]  << std::endl;
//    }
}

void web::draw(){
  //if (ofGetKeyPressed()) {
  //mesh.disableNormals();
//} else {
ofSetColor(ofColor::white);

//triang.draw();
ofNoFill();

ofSetColor(ofColor::blue);
//susu.drawNormalEnd(mesh.getNormal(susu.indexEnd));

//}

//ofSetColor(ofColor(150,150,150));
//mesh.drawWireframe();
//  mesh.drawFaces();
ofSetColor(ofColor::blue);

  triangulation.draw();
  susu.draw();
}


// void web::calcNormals() {
// 	for( int i=0; i < mesh.getVertices().size(); i++ ) mesh.addNormal(ofPoint(0,0,0).normalize());
//
// 	for( int i=0; i < mesh.getIndices().size(); i+=3 ){
// 		const int ia = mesh.getIndices()[i];
// 		const int ib = mesh.getIndices()[i+1];
// 		const int ic = mesh.getIndices()[i+2];
//
// 		ofVec3f e1 = mesh.getVertices()[ia] - mesh.getVertices()[ib];
// 		ofVec3f e2 = mesh.getVertices()[ic] - mesh.getVertices()[ib];
// 		ofVec3f no = e2.cross( e1 );
//
// 		mesh.getNormals()[ia] += no;
// 		mesh.getNormals()[ib] += no;
// 		mesh.getNormals()[ic] += no;
// 	}
//
// }
