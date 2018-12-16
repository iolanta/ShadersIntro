#version 410

uniform vec3 color;
in vec3 normf;
in vec2 texcoordf;
in vec3 colorf;
out vec4 fragColor;

void main(){
	fragColor = vec4(color, 1.0);
}