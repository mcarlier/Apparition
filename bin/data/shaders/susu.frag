#version 150
#define PI 3.14159265359

uniform sampler2DRect tex0;
uniform vec2 u_resolution;
uniform float u_time;
in vec2 texCoordVarying;
out vec4 outputColor;


void main(void) {

  outputColor = texture(tex0, texCoordVarying);

}
