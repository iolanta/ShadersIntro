#version 410
in vec3 normf;
in vec2 texcoordf;
in vec3 colorf;
out vec4 color;
uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;
uniform float mix_coef;

void main(){
	color = mix(texture(ourTexture, texcoordf), texture(ourTexture2, texcoordf), mix_coef);
}