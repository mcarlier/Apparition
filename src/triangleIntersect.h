#pragma once

#include "ofMain.h"
#define EPSILON2 0.000001

class triangle_intersection {
public:
Boolean test(  ofVec3f  V1,  // Triangle vertices
                            ofVec3f   V2,
                            ofVec3f   V3,
                            ofVec3f    O,  //Ray origin
                            ofVec3f    D,  //Ray direction
                                 float* out );
};
