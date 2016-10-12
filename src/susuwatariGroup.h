#pragma once
#include "ofMain.h"
#include "susuwatari.h"



class susuwatariGroup{
	public:
    int setup(int NumSusuwatari,vector<ofMeshFace> triangles,int triangleDrawn);
    int update(vector<ofMeshFace> triangles,int totalTriangle, int triangleDrawn);
    void draw();

    vector<susuwatari> susuwataris;

    ofTexture texture;
    ofShader shaderSusu;
    ofVbo vboSusu;

    void addPoint(float x, float y, float z);
    // vector to store all values
    vector <ofVec3f> pointsSusu;
    vector <ofVec3f> sizesSusu;

};
