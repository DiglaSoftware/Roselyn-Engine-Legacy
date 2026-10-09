#ifndef STATIC_MESH_HPP
#define STATIC_MESH_HPP

#include "RoselynObject.hpp"
#include "ShaderWorker.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"
#include <string>
#include <glm/glm.hpp>
#include <vector>

namespace RoselynEngine {
	class StaticMesh : public RoselynObject {
		public:
			StaticMesh();
			~StaticMesh();

			void Draw() override;

			void SetShaderWorker(ShaderWorker &shaderWorker);
			void SetTexture(Texture &texture);
			void SetMesh(Mesh &mesh);
		private:
			ShaderWorker* MeshShaderWorker = nullptr; // mesh material
			Texture* MeshTexture = nullptr;
			Mesh* ObjectMesh = nullptr;
	};
}

#endif /* STATIC_MESH_HPP */