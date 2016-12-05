#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//ofSetVerticalSync(true);
	kinect.setup();
	web.setup();
	shader.load("shaders/glitch");
	sound.setup();
	timerDetectionStill.setup(2000);
	timerPeopleOut.setup(5000);
	imageSaved = false;
	restart = false;
	counterUser.setup();
	text.setup(counterUser.getString());


	std::cout << counterUser.getInt() << '\n';
	std::cout << counterUser.getString() << '\n';
	counterUser.increment();


}

//--------------------------------------------------------------
void ofApp::update(){
	if (!base.isAllocated()) {
		base = kinect.base;
		web.base = base;
	}
	else{
		web.update();
	}
	ofSoundUpdate();

	kinect.update();
	sound.update();
	timerDetectionStill.update();
	timerPeopleOut.update();
	stateManager();

	if (restart&&!timerPeopleOut.bIsRunning) {
			startAnew();
	}
	if ((web.state==2)&&(imageSaved==false)&&(web.triangleDrawn>=web.triangulation.getNumTriangles()/2)) {
		kinect.saveImage();
		counterUser.increment();
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
	shader.begin();
	shader.setUniform1f("u_time", ofGetElapsedTimef());
	std::cout <<ofGetElapsedTimef() << '\n';
	shader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
	if (base.isAllocated()) {
		base.draw(0,0);
	}
	shader.end();
	ofPopMatrix();
	if((!web.end)&&(!web.waitPeopleToGo)){
		kinect.draw(shader);
	}
	web.draw(shader,sound.avg);

	//sound.draw();

	cam.end();

	//timerDetectionStill.draw( 15 , 15 ) ;
	//timerPeopleOut.draw(ofGetWidth() /2 + 15 , 15);
	text.draw(web.waitPeopleToGo,web.end,web.state);

}

void ofApp::exit() {
    kinect.threadDetection.stopThread();
}
void ofApp::startAnew(){
	std::cout << "startAnew" << '\n';
	kinect.loadNewImage();
	if(kinect.loadState==2){
		web.startAnew(kinect.imageLoaded);
		imageSaved = false;
		kinect.loadState = 0;
		restart=false;
		text.update(counterUser.getString());
	}
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
	if(!web.end){
		if(!web.waitPeopleToGo){
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
			if ((timerDetectionStill.bIsRunning)&&(web.state!=2)) {
				if(timerDetectionStill.getNormalizedProgress()-0.95>=0){
					web.changeState(2);
				}
			}
		}
		else{
			if(kinect.changeState==0){
				timerPeopleOut.start(false);
				restart=true;
			}
			else if((kinect.changeState==1)||(kinect.changeState==-1)){
				timerPeopleOut.reset();
				restart=false;
			}
		}
	}
}
void ofApp::peopleOutManager(){
	if(kinect.changeState==0){
		web.changeState(0);
		timerDetectionStill.reset();
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
	 std::cout << "x = "<< x << '\n';
	 std::cout << "y = "<<  y<< '\n';

	 	//std::cout << "saveImage " << '\n';
		//kinect.saveImage();
	 	web.setupEnd();
	 	//startAnew();



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
