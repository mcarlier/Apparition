#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//ofSetVerticalSync(true);
	kinect.setup();
	web.setup();
	shader.load("shaders/susu");
	base.load("img.jpg");

	sound.setup();

	timerDetectionStill.setup(2000);
	timer2.setup(750);
	imageSaved = false;
	timer2.start(false);

}

//--------------------------------------------------------------
void ofApp::update(){
	ofSoundUpdate();
	web.update();
	kinect.update();
	sound.update();
	timerDetectionStill.update( ) ;
	timer2.update( ) ;
	stateManager();

	if ((web.state==2)&&(imageSaved==false)&&(web.triangleDrawn>=web.triangulation.getNumTriangles()/2)) {
		std::cout << "saveImage" << '\n';
		kinect.saveImage();
		imageSaved=true;
	}


}

//--------------------------------------------------------------

void ofApp::draw(){

	ofBackground(0,0,0);
	cam.begin();
	ofPushMatrix();
	ofScale(ofVec3f(0.65));
	ofTranslate(-base.getWidth()/2,-base.getHeight()/2,0);
	//gui.draw();
	//shader.begin();
	shader.setUniform1f("u_time", ofGetElapsedTimef());
	shader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
	base.draw(0,0);
	ofPopMatrix();

	kinect.draw();

	web.draw(sound.avg);

	//sound.draw();

	cam.end();
	//shader.end();


	// timerDetectionStill.draw( 15 , 15 ) ;
	// timer2.draw( ofGetWidth() /2 + 15 , 15 ) ;
}

void ofApp::exit() {
    kinect.threadDetection.stopThread();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(web.state == 0){
		web.changeState(1);
	}
	else if(web.state == 1){
		web.changeState(2);
	}
	else{
		web.changeState(0);
	}
}

void ofApp::stateManager(){
	if (kinect.changeState==1) {//someoneDetected
		web.changeState(1);
		timerDetectionStill.start(false);
	}
	else if(kinect.changeState==-1) {//someoneMoving
		web.changeState(1);
		timerDetectionStill.reset();
	}
	else if(kinect.changeState==0){
		web.changeState(0);
		timerDetectionStill.reset();
	}
	if (timerDetectionStill.bIsRunning) {
		if(timerDetectionStill.getNormalizedProgress()-0.97>=0){
			web.changeState(2);
		}
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
	// std::cout << "x = "<< x << '\n';
	// std::cout << "y = "<<  y<< '\n';
	std::cout << "saveImage " << '\n';
	 kinect.saveImage();


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
