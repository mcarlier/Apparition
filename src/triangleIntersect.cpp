#include "triangleIntersect.h"

Boolean triangle_intersection::test(  ofVec3f  V1,  // Triangle vertices
                            ofVec3f   V2,
                            ofVec3f   V3,
                            ofVec3f    O,  //Ray origin
                            ofVec3f    D,  //Ray direction
                                 float* out )
{
  ofVec3f e1, e2;  //Edge1, Edge2
  ofVec3f P, Q, T;
  float det, inv_det, u, v;
  float t;

  //Find vectors for two edges sharing V1
  e1= V2-V1;
  e2= V3-V1;
  //Begin calculating determinant - also used to calculate u parameter
  P= D.cross(e2);
  //if determinant is near zero, ray lies in plane of triangle or ray is parallel to plane of triangle
  det = e1.dot(P);
  //NOT CULLING
  if(det > -EPSILON && det < EPSILON) return 0;
  inv_det = 1.f / det;

  //calculate distance from V1 to ray origin
  T= O-V1;

  //Calculate u parameter and test bound
  u = T.dot(P) * inv_det;
  //The intersection lies outside of the triangle
  if(u < 0.f || u > 1.f) return 0;

  //Prepare to test v parameter
  Q= T.cross(e1);

  //Calculate V parameter and test bound
  v = D.dot(Q) * inv_det;
  //The intersection lies outside of the triangle
  if(v < 0.f || u + v  > 1.f) return 0;

  t = e2.dot(Q) * inv_det;

  if(t > EPSILON) { //ray intersection
    *out = t;
    return true;
  }

  // No hit, no win
  return false;
}
