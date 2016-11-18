#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//ofSetVerticalSync(true);
	kinect.setup();
	web.setup();
	shader.load("shaders/noise");
	base.load("imgLeft.jpg");
}

//--------------------------------------------------------------
void ofApp::update(){
	web.update();
	kinect.update();
}

//--------------------------------------------------------------

void ofApp::draw(){

	ofBackground(0,0,0);
	cam.begin();
	ofPushMatrix();
	ofScale(ofVec3f(0.65));
	ofTranslate(-base.getWidth()/2,-base.getHeight()/2,0);
	shader.begin();
	shader.setUniform1f("u_time", ofGetElapsedTimef());
	shader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
	base.draw(0,0);
	ofPopMatrix();

	kinect.draw();

	web.draw();
	shader.end();

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
