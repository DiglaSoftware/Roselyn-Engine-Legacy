#version 330 core

in vec2 TextureCoordinate;
in vec3 Normal;

out vec4 FragColor;

uniform float ambientStrength;
uniform vec3 ambientColor;
uniform sampler2D Texture;

void main() {
	vec4 textureColor = texture(Texture, TextureCoordinate);

	vec3 result = ambientStrength * ambientColor + textureColor.rgb;
	FragColor = vec4(result, textureColor.a);
}