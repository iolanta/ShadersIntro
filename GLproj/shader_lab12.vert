#version 410
attribute vec4 coord;
attribute vec3 norm;
attribute vec2 texcoord;
attribute vec3 color;
out vec3 normf;
out vec2 texcoordf;
out vec3 colorf;
uniform mat4 transf;

void main(){
	gl_Position = transf * coord;
	normf = norm;
	texcoordf = texcoord;
	colorf = color;
}