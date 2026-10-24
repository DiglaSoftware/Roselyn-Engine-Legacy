#include "AssetWarehouse.hpp"

#include <iostream>

namespace RoselynEngine {
	std::unordered_map<std::string, Texture*> AssetWarehouse::Textures = {};
	std::unordered_map<std::string, Mesh*> AssetWarehouse::Meshes = {};

	void AssetWarehouse::Init() {
	
	}

	bool AssetWarehouse::LoadTexture(const std::string& filePath, const std::string textureName) {
		if (AssetWarehouse::Textures.contains(textureName)) {
			std::cout << "ROSELYN::ASSET-WAREHOUSE | Texture with name \"" << textureName << "\" already exists, loading aborted" << std::endl;
			return false;
		}

		Texture* newTexture = new Texture();
		newTexture->LoadFromFile(filePath);

		AssetWarehouse::Textures[textureName] = newTexture;
		
		std::cout << "ROSELYN::ASSET-WAREHOUSE | Texture " << textureName << " loaded" << std::endl;

		return true;
	}

	Texture* AssetWarehouse::GetTexture(const std::string& textureName) {
		if (AssetWarehouse::Textures.contains(textureName)) {
			return AssetWarehouse::Textures[textureName];
		}
		else {
			return nullptr;
		}
	}

	void AssetWarehouse::UnloadTexture(const std::string& textureName) {
		if (AssetWarehouse::Textures.contains(textureName)) {
			delete AssetWarehouse::Textures[textureName];
			AssetWarehouse::Textures.erase(textureName);
		}
	}

	bool AssetWarehouse::IsTextureLoaded(const std::string& textureName) {
		return AssetWarehouse::Textures.contains(textureName);
	}

	// meshhhhhhhhhhhh

	bool AssetWarehouse::LoadMesh(const std::string& filePath, const std::string meshName) {
		if (AssetWarehouse::Meshes.contains(meshName)) {
			std::cout << "ROSELYN::ASSET-WAREHOUSE | Mesh with name \"" << meshName << "\" already exists, loading aborted" << std::endl;
			return false;
		}

		Mesh* newMesh = new Mesh(filePath);

		AssetWarehouse::Meshes[meshName] = newMesh;

		std::cout << "ROSELYN::ASSET-WAREHOUSE | Mesh " << meshName << " loaded" << std::endl;

		return true;
	}

	Mesh* AssetWarehouse::GetMesh(const std::string& meshName) {
		if (AssetWarehouse::Meshes.contains(meshName)) {
			return AssetWarehouse::Meshes[meshName];
		}
		else {
			return nullptr;
		}
	}

	void AssetWarehouse::UnloadMesh(const std::string& meshName) {
		if (AssetWarehouse::Meshes.contains(meshName)) {
			delete AssetWarehouse::Meshes[meshName];
			AssetWarehouse::Meshes.erase(meshName);
		}
	}

	bool AssetWarehouse::IsMeshLoaded(const std::string& meshName) {
		return AssetWarehouse::Meshes.contains(meshName);
	}
}