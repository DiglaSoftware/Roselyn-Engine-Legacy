#version 330 core

layout (location = 0) in vec3 VertexLocalPos;
layout (location = 1) in vec2 VertexTextureCoordinate;
layout (location = 2) in vec3 VertexNormal;

out vec2 TextureCoordinate;
out vec3 Normal;

uniform mat4 Model;
uniform mat4 ViewProjection;

void main() {
	gl_Position = ViewProjection *  Model * vec4(VertexLocalPos.x, VertexLocalPos.y, VertexLocalPos.z, 1.0);
	TextureCoordinate = VertexTextureCoordinate;
	Normal = VertexNormal;
}