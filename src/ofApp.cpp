#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//ofSetVerticalSync(true);
	kinect.setup();
	web.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
	web.update();
	kinect.update();
}

//--------------------------------------------------------------

void ofApp::draw(){

	ofBackgroundGradient(ofColor(200), ofColor(150));

	ofSetColor(255);
	cam.begin();
	kinect.draw();
	web.draw();

	cam.end();


}

void ofApp::exit() {
    kinect.threadDetection.stopThread();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(web.state != 1){
		web.changeState();
	}
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
