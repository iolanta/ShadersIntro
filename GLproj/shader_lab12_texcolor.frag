#version 410

in vec3 normf;
in vec2 texcoordf;
in vec3 colorf;
out vec4 color;
uniform sampler2D ourTexture;

void main(){
	color = texture(ourTexture, texcoordf) * vec4(colorf, 1.0f);
}