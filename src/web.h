#pragma once
#include "ofMain.h"
#include "webSample.h"
#include "ofxDelaunay.h"

//TPM :
#include "ofxDatGui.h"

class web : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		void changeState();
		int state;
		vector<webSample> webSamples;
		int NumWebSample;
		ofxDelaunay triangulation;
		ofMesh mesh;

		//Vbo dealing :
		ofVbo vboSusu;
		vector <ofVec3f> pointsSusu;
		vector <ofVec3f> sizesSusu;
		ofTexture texture;
		ofShader shaderSusu;

		ofShader shaderWeb;


		int positionMesh; //1 = right / 2 = left;
		ofImage RVB;
		ofImage Depth;
		ofImage RVB0;
		ofImage Depth0;
		ofMesh meshRight;
		ofxDelaunay triangulationRight;
		ofMesh meshLeft;
		ofxDelaunay triangulationLeft;
		void createMesh();
		//TMP
		ofxDatGui* gui;
		void onSliderEvent(ofxDatGuiSliderEvent e);
		ofParameter<int> x;
		ofParameter<int> y;
		ofParameter<float> dx;
		ofParameter<float> dy;

		ofxDatGuiLabel*  l1;
		ofxDatGuiSlider* s1;
		ofxDatGuiSlider* s2;
		ofxDatGuiSlider* s3;
		ofxDatGuiSlider* s4;




		//apprearance
		void setup_appeared();
		void update_appeared();
		int triangleDrawn;
		vector<ofMeshFace> triangles;
		ofPlanePrimitive plane;

};
