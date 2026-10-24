#ifndef STATIC_MESH_HPP
#define STATIC_MESH_HPP

#include "RoselynObject.hpp"
#include <string>
#include "Texture.hpp"
#include "Mesh.hpp"

namespace RoselynEngine {
	enum ShaderType {
		Unlit,
		Lit
	};

	class StaticMesh : public RoselynObject {
		public:
			StaticMesh();
			StaticMesh(std::string meshName, std::string textureName);
			~StaticMesh();

			void Draw() override;
			void Tick() override;

			void SetTexture(std::string textureName);
			void SetMesh(std::string meshName);
			void SetShader(ShaderType shaderType);
		private:
			Texture* MeshTexture = nullptr;
			Mesh* ObjectMesh = nullptr;
			ShaderType CurrentShader = Unlit;
	};
}

#endif /* STATIC_MESH_HPP */