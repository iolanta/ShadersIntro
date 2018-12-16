#version 410

uniform vec3 color;
in vec3 normf;
in vec2 texcoordf;
in vec3 colorf;

void main(){
	gl_FragColor = color;
}