#version 150
#define PI 3.14159265359

uniform sampler2DRect tex0;
uniform vec2 u_resolution;
uniform float u_time;
uniform float a;
uniform float b;
uniform float c;
uniform float d;





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


vec2 deformation(){
  vec2 st = gl_FragCoord.xy/u_resolution.xy*3.;
  // float x = gl_FragCoord.x/u_resolution.x*3.;
  // float y = gl_FragCoord.y/u_resolution.y*3.;
  // float amplitude = 1.;
  // float frequency = 1.;
  // y = sin(x * frequency);
  // float t = 0.01*(-u_time*130.0);
  // y += sin(x*frequency*2.1 + t)*4.5;
  // y += sin(x*frequency*1.72 + t*1.121)*4.0;
  // y += sin(x*frequency*2.221 + t*0.437)*5.0;
  // y += sin(x*frequency*3.1122+ t*4.269)*2.5;
  // y *= amplitude*0.06;
  // // gl_FragCoord.y = y;
  // return vec2(5*y,10*y);

  vec4 col = texture(tex0,texCoordVarying);
  float rand1 = random(vec2(u_time));
  // vec4 col_s = texture(tex0,texCoordVarying + 100*vec2(floor(sin(st.y/30.0*rand1+rand1*rand1))*30.0*rand1,0));
  // col = col_s;

  vec2 result=vec2(1);
// Assign a random value based on the integer coord
  if(mod(floor(u_time),20)==0){
    vec2 st1 = st*10.; // Scale the coordinate system by 10
    vec2 ipos = floor(st1);  // get the integer coords
    result += vec2(50*fract(sin(ipos.y +sin(u_time)*1.0)),0);
  }
  else if(mod(floor(u_time),35)==0){
    vec2 st2 = st*random(st +sin(u_time)); // Scale the coordinate system by 10
    vec2 ipos = floor(st2);  // get the integer coords
    result+= vec2(50*fract(sin(ipos.y +sin(u_time)*1.0)),0);
  }
  return result;

}
vec4 convergence(){
  vec2 st = gl_FragCoord.xy/u_resolution.xy*3.;
   vec2 deformationG = deformation();

  vec4 col = texture(tex0,texCoordVarying+ deformationG);
  int a = int(u_time/4);
  vec4 col_r = texture(tex0,texCoordVarying+deformationG+ vec2(-35.0*random(vec2(u_time))*u_time,0));
  vec4 col_l = texture(tex0,texCoordVarying+deformationG+ vec2( 35.0*random(vec2(a)),0));
  vec4 col_g = texture(tex0,texCoordVarying+deformationG+ vec2( -70.5*random(vec2(a)),0));


  col.b = col.b + col_r.b*max(0.3,sin(st.y*2)*0.5)*random(vec2(sin(int(u_time/2))));
  col.r = col.r + col_l.r*max(0.3,sin(st.y*2)*0.5)*random(vec2(sin(int(u_time/2))));
  col.g = col.g + col_g.g*max(0.3,sin(st.y*2)*0.5)*random(vec2(sin(int(u_time/2))));

  return col;
}



void main() {

    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    float y =smoothstep(0.325,0.5,st.x) - smoothstep(0.6,0.785,st.x);
    vec4 col = convergence();
    col.a *= y;
	  outputColor = col;

    //outputColor = texture(tex0,texCoordVarying +vec2(10*y,10*y));


    //outputColor = texture(tex0, texCoordVarying)*vec4(1,1,sin(u_time),1);//-vec4((f*f*f+.6*f*f+.5*f)*color,color.x));
}

	//outputColor = texture(tex0, texCoordVarying)*vec4(color,1.0);
