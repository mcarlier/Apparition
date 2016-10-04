#include "ofApp.h"

ofMesh meshCross;

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
//	meshCross.addVertex(mesh.getVertex(10));
//	meshCross.addVertex(mesh.getVertex(200));
	web.setup();
  //meshCross.addVertex(mesh.getVertex(1));
	//Pyramid's base vertices with indices 0, 1, 2
}

//--------------------------------------------------------------
void ofApp::update(){
	web.update();
}

//--------------------------------------------------------------

void ofApp::draw(){
	ofBackgroundGradient(ofColor(200), ofColor(150));

	ofSetColor(255);
	cam.begin();



	web.draw();

	///ofSetColor(ofColor::green);
//	ofSetColor(ofColor::green);
//	ofDrawLine(meshCross.getVertex(0),meshCross.getVertex(1));
	//ofNoFill();^
	//meshCross.draw();
//	int n = mesh.getNumVertices()-1;
	// for(int i = 0; i < n; i++) {
	// 	cout << i << endl;
	// 	ofSetColor(ofColor::green);
	// 	ofDrawLine(mesh.getVertex(i),mesh.getVertex(i+1));
	//
	// }



	cam.end();

	// int n = meshCross.getNumVertices()-1;
	//float nearestDistance = 0;
	//ofVec2f nearestVertex;
	//int nearestIndex = 0;
	//ofVec2f mouse(mouseX, mouseY);
	//cout << n << endl;
	//meshCross.draw();
	// ofSetColor(ofColor::green);
	// ofDrawLine(meshCross.getVertex(0),meshCross.getVertex(1));
	// for(int i = 0; i < n; i++) {
	// 	cout << i << endl;
	// 	ofSetColor(ofColor::green);
	// 	ofDrawLine(meshCross.getVertex(i),meshCross.getVertex(i+1));
		//ofVec3f cur = cam.worldToScreen(mesh.getVertex(i));
		//float distance = cur.distance(mouse);
		//if(i == 0 || distance < nearestDistance) {
		//	nearestDistance = distance;
		// 	nearestVertex = cur;
		// 	nearestIndex = i;
		// }
	//}

	//ofSetColor(ofColor::gray);
	//ofDrawLine(nearestVertex, mouse);
	//ofNoFill();
	// ofSetColor(ofColor::yellow);
	// ofSetLineWidth(2);
	// ofDrawCircle(nearestVertex, 4);
	// ofSetLineWidth(1);
	//
	// ofVec2f offset(10, -10);
	// ofDrawBitmapStringHighlight(ofToString(nearestIndex), mouse + offset);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
