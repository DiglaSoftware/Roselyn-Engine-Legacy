#include "StaticMesh.hpp"
#include "AssetWarehouse.hpp"
#include "Engine.hpp"
#include <glad/glad.h>

namespace RoselynEngine {
	StaticMesh::StaticMesh() {
		
	}

	StaticMesh::StaticMesh(std::string meshName, std::string textureName) {
		this->ObjectMesh = AssetWarehouse::GetMesh(meshName);
		this->MeshTexture = AssetWarehouse::GetTexture(textureName);
	}

	StaticMesh::~StaticMesh() {
	
	}

	void StaticMesh::Draw() {
		if (this->MeshTexture != nullptr)
			this->MeshTexture->Use();

		if (this->ObjectMesh != nullptr)
			this->ObjectMesh->Draw();

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void StaticMesh::Tick() { }

	void StaticMesh::SetTexture(std::string textureName) {
		if (AssetWarehouse::IsTextureLoaded(textureName))
			this->MeshTexture = AssetWarehouse::GetTexture(textureName);
	}

	void StaticMesh::SetMesh(std::string meshName) {
		if (AssetWarehouse::IsMeshLoaded(meshName))
			this->ObjectMesh = AssetWarehouse::GetMesh(meshName);
	}

	void StaticMesh::SetShader(ShaderType shader) {
		this->CurrentShader = shader;
	}
}