#ifndef ASSET_WAREHOUSE_HPP
#define ASSET_WAREHOUSE_HPP

#include "Texture.hpp"
#include "Mesh.hpp"

#include <string>
#include <unordered_map>

namespace RoselynEngine {
	class AssetWarehouse {
		public:
			static void Init();

			static bool LoadTexture(const std::string& filePath, const std::string textureName);
			static Texture* GetTexture(const std::string& textureName);
			static void UnloadTexture(const std::string& textureName);
			static bool IsTextureLoaded(const std::string& textureName);

			static bool LoadMesh(const std::string& filePath, const std::string meshName);
			static Mesh* GetMesh(const std::string& meshName);
			static void UnloadMesh(const std::string& meshName);
			static bool IsMeshLoaded(const std::string& meshName);

			static void UnloadAll();
			static void UnloadAllTextures();
			static void UnloadAllMeshes();

		private:
			static std::unordered_map<std::string, Texture*> Textures;
			static std::unordered_map<std::string, Mesh*> Meshes;
	};
}

#endif /* ASSET_WAREHOUSE_HPP */