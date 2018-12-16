#version 4605

uniform int width;
uniform vec3 color1;
uniform vec3 color2;
in vec3 normf;
in vec2 texcoordf;
in vec3 colorf;

void main(){
	if(mod(gl_FragCoord.y, width / 2) < width)
		gl_FragColor = color1;
	else
		gl_FragColor = color2;
}