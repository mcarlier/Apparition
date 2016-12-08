#include "faceAppeare.h"

void faceAppeare::setup(int duration,ofMeshFace points){
  timerappearance.setup(duration);
  timerappearance.start(false);
  lastFace.addVertex(points.getVertex(0));
  lastFace.addTexCoord(points.getTexCoord(0));
  lastFace.addVertex(points.getVertex(1));
  lastFace.addTexCoord(points.getTexCoord(1));
  lastFace.addVertex(points.getVertex(2));
  lastFace.addTexCoord(points.getTexCoord(2));
}
