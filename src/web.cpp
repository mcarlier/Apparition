#include "web.h"

void web::setup(){
  mesh.load("lofi-bunny.ply");
  int indexVertexEnd = rand() % mesh.getNumVertices();
  susu.setup(mesh.getVertex(rand() % mesh.getNumVertices()),mesh.getVertex(indexVertexEnd),indexVertexEnd);
  calcNormals();



}

//--------------------------------------------------------------
void web::update(){
  if (susu.betweenStartAndEnd()){
    susu.update();
  }
  else{
    float dot = 1;
    int indexVertex = rand() % mesh.getNumVertices();
    while((dot>0)||(!susu.testNextPosition(mesh,indexVertex))){
      dot = mesh.getNormal(indexVertex).dot(mesh.getNormal(susu.indexEnd));
      std::cout << dot << std::endl;
    }
    std::cout << "dot :" << std::endl;

    susu.changeDirection(mesh.getVertex(indexVertex),indexVertex);
  }
}

void web::draw(){
  //if (ofGetKeyPressed()) {
  //mesh.disableNormals();
//} else {
ofSetColor(ofColor::blue);
susu.drawNormalEnd(mesh.getNormal(susu.indexEnd));

//}
susu.draw();
ofSetColor(ofColor(150,150,150));
mesh.drawWireframe();
//  mesh.drawFaces();

}
void web::calcNormals() {
	for( int i=0; i < mesh.getVertices().size(); i++ ) mesh.addNormal(ofPoint(0,0,0).normalize());

	for( int i=0; i < mesh.getIndices().size(); i+=3 ){
		const int ia = mesh.getIndices()[i];
		const int ib = mesh.getIndices()[i+1];
		const int ic = mesh.getIndices()[i+2];

		ofVec3f e1 = mesh.getVertices()[ia] - mesh.getVertices()[ib];
		ofVec3f e2 = mesh.getVertices()[ic] - mesh.getVertices()[ib];
		ofVec3f no = e2.cross( e1 );

		mesh.getNormals()[ia] += no;
		mesh.getNormals()[ib] += no;
		mesh.getNormals()[ic] += no;
	}

}
