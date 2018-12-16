#version 410

uniform matr4 transforms;
attribute vec4 coord;
attribute vec3 norm;
attribute vec2 texcoord;
attribute vec3 color;
out vec3 normf;
out vec2 texcoordf;
out vec3 colorf;

void main(){
	gl_Position = transforms * coord;
	normf = norm;
	texcoordf = texcoord;
	colorf = color;
}