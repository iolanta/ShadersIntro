#version 410

uniform int width;
uniform vec3 color1;
uniform vec3 color2;
in vec3 normf;
in vec2 texcoordf;
in vec3 colorf;
out vec4 fragColor;

void main(){
	if(mod(gl_FragCoord.y, width / 2) < width)
		fragColor = vec4(color1, 1.0);
	else
		fragColor = vec4(color2,1.0);
}