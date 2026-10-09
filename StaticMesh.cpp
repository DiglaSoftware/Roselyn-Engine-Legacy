#include "StaticMesh.hpp"
#include "ShaderWorker.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"
#include <glad/glad.h>

namespace RoselynEngine {
	StaticMesh::StaticMesh() {
		
	}

	StaticMesh::~StaticMesh() {
	
	}

	void StaticMesh::Draw() {
		if (this->MeshTexture != nullptr)
			this->MeshTexture->Use();

		ObjectMesh->Use();
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void StaticMesh::SetShaderWorker(ShaderWorker &shaderWorker) {
		this->MeshShaderWorker = new ShaderWorker(shaderWorker);
	}

	void StaticMesh::SetTexture(Texture &texture) {
		this->MeshTexture = new Texture(texture);
	}

	void StaticMesh::SetMesh(Mesh &mesh) {
		this->ObjectMesh = new Mesh(mesh);
	}
}