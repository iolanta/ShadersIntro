#version 4605

in vec3 normf;
in vec2 texcoordf;
in vec3 colorf;
out vec4 color;
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform int mix_coef;

void main(){
	color = mix(texture(ourTexture1, texcoordf), texture(ourTexture2, texcoordf), mix_coef);
}