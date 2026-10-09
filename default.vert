#version 330 core

layout (location = 0) in vec3 VertexLocalPos;
layout (location = 1) in vec2 VertexTextureCoordinate;

out vec2 TextureCoordinate;

uniform mat4 Model;
uniform mat4 ViewProjection;

void main() {
	gl_Position = ViewProjection *  Model * vec4(VertexLocalPos.x, VertexLocalPos.y, VertexLocalPos.z, 1.0);
	TextureCoordinate = VertexTextureCoordinate;
}