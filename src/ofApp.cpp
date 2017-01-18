#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//ofSetVerticalSync(true);
	ofxJSONElement infos;
	infos.open("values.json");
	kinect.setup(stoi(infos["kinect"]["PresencePrecision"].asString()),stoi(infos["kinect"]["MotionPrecision"].asString()));
	shader.load("shaders/glitch");
	shaderweb.load("shaders/glitch_web");
	sound.setup();
	timerDetectionStill.setup(stoi(infos["App"]["timerDetectionStill"].asString())); //How much time the person stay still before draw
	timerPeopleOut.setup(stoi(infos["App"]["timerPeopleOut"].asString()));//How much time noone before restart
	imageSaved = false;
	restart = false;
	counterUser.setup();
	text.setup(counterUser.getString());
	int lastuserID = (counterUser.getInt()-1)%5;
	web.setup(infos["web"],to_string(lastuserID));

	std::cout << counterUser.getString() << '\n';

	gui.setup(); //Update : no need
	gui.add(radius.setup("radius", 140, 10, 300));
	gui.add(random_base.setup("random_base", 2, 0, 5));
	gui.add(b.setup("b", 0.5, 0, 2));
	gui.add(c.setup("c", 2, 0, 10));


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
	sound.update();
	kinect.update();
	timerDetectionStill.update();
	timerPeopleOut.update();
	stateManager();
	if (restart&&!timerPeopleOut.bIsRunning) {
			startAnew();
	}
	if ((web.state==2)&&(imageSaved==false)&&(web.triangleDrawn>=web.triangulation.getNumTriangles()/2)) {
		kinect.saveImage(counterUser.getInt());
		counterUser.increment();
		imageSaved=true;
	}
	currentTime = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0,0,0);
	cam.begin();
	ofPushMatrix();
	ofScale(ofVec3f(0.65));
	ofTranslate(-base.getWidth()/2,-base.getHeight()/2,0);
	shader.begin();
	shader.setUniform1f("u_time", currentTime);
	shader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());

	if (base.isAllocated()) {
		base.draw(0,0);
	}
	shader.end();
	ofPopMatrix();
	if((!web.end)||(web.multipleFade.started==true)){
		kinect.draw(shader,currentTime);
	}
	web.draw(shader,shaderweb,sound.avg,currentTime);
	cam.end();
  //web.gui.draw();

	//timerDetectionStill.draw( 15 , 15 ) ;
	//timerPeopleOut.draw(ofGetWidth() /2 + 15 , 15);

	text.draw(web.waitPeopleToGo,web.multipleFade.started,web.end,web.state);
}

//Stop all te thread before quitting
void ofApp::exit() {
    kinect.threadDetection.stopThread();
		kinect.threadLoadImage.stopThread();
		kinect.threadSaveImage.stopThread();
}
//Initialise the system for the next user.
void ofApp::startAnew(){
	std::cout << "startAnew" << '\n';
	// kinect.loadNewImage();
	// if(kinect.loadState==2){
		web.startAnew(kinect.imageLoaded);
		imageSaved = false;
		kinect.loadState = 0;
		restart=false;
		text.update(counterUser.getString());
	// }
}
//Make a link between the kinect movement detection and the web behavior
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
			if(!web.setupWaitPeopleToGo){
				if(kinect.stateDetection==0){
					timerPeopleOut.start(false);
					restart=true;
				}
				web.setupWaitPeopleToGo=true;
			}
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
//manage timer that indicate that the user is out.
void ofApp::peopleOutManager(){
	if(kinect.changeState==0){
		web.changeState(0);
		timerDetectionStill.reset();
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
