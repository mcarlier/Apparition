#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//ofSetVerticalSync(true);
	web.setup();
	rotation = 0;
	// cam.disableMouseInput();
	// cam.enableMouseMiddleButton();

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
		//ofRotate(rotation,0,1,0);

	web.draw();

	//ofRotate(-rotation,0,1,0);
	rotation+=0.05;

	cam.end();


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(web.state != 1){
	web.changeState();
}
	//web.update();
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
