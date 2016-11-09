#include "web.h"

void web::setup_appeared(){
  triangleDrawn = 0;
  triangles = triangulation.triangleMesh.getUniqueFaces();
  for (size_t i = 0; i < webSamples.size(); i++) {
    webSamples[i].setup_appeared(triangles[triangleDrawn]);
    triangleDrawn ++;
  }
}

void web::update_appeared(){
  for (size_t i = 0; i < webSamples.size(); i++) {
    if( webSamples[i].state_appeared == 0 && triangleDrawn < triangulation.getNumTriangles()){
      webSamples[i].addTriangle_appeared(triangles[triangleDrawn]);
      triangleDrawn ++;
    }
    webSamples[i].update_appeared();
  }
}
