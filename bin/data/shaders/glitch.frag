#version 150
#define PI 3.14159265359

uniform sampler2DRect tex0;
uniform vec2 u_resolution;
uniform float u_time;


in vec2 texCoordVarying;
out vec4 outputColor;

float random (in vec2 _st) {
    return fract(sin(dot(_st.xy,
                         vec2(12.9898,78.233)))*
        43758.5453123);
}

// Based on Morgan McGuire @morgan3d
// https://www.shadertoy.com/view/4dS3Wd
float noise (in vec2 _st) {
    vec2 i = floor(_st);
    vec2 f = fract(_st);

    // Four corners in 2D of a tile
    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    vec2 u = f * f * (3.0 - 2.0 * f);

    return mix(a, b, u.x) +
            (c - a)* u.y * (1.0 - u.x) +
            (d - b) * u.x * u.y;
}



vec4 convergence() {
  vec2 st = gl_FragCoord.xy/u_resolution.xy*3.;

  vec4 col = texture(tex0,texCoordVarying);
  int a = int(u_time);
  vec4 col_r = texture(tex0,texCoordVarying + vec2(-35.0*random(vec2(u_time))*u_time,0));

  vec4 col_l = texture(tex0,texCoordVarying + vec2( 35.0*random(vec2(a)),0));
  vec4 col_g = texture(tex0,texCoordVarying + vec2( -70.5*random(vec2(a)),0));


  col.b = col.b + col_r.b*max(1.0,sin(st.y*2)*0.5)*random(vec2(2));
  col.r = col.r + col_l.r*max(1.0,sin(st.y*2)*0.5)*random(vec2(2));
  col.g = col.g + col_g.g*max(1.0,sin(st.y*2)*0.5)*random(vec2(2));

  return col;
}

void main() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy*3.;

	outputColor = convergence();


    //outputColor = texture(tex0, texCoordVarying)*vec4(1,1,sin(u_time),1);//-vec4((f*f*f+.6*f*f+.5*f)*color,color.x));
}

	//outputColor = texture(tex0, texCoordVarying)*vec4(color,1.0);
