#ifndef MESH_HPP
#define MESH_HPP

#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace RoselynEngine {
	struct Vertex {
		glm::vec3 Position;
		glm::vec2 TexCoords;

		bool operator<(const Vertex& o) const {
			if (Position.x != o.Position.x) return Position.x < o.Position.x;
			if (Position.y != o.Position.y) return Position.y < o.Position.y;
			if (Position.z != o.Position.z) return Position.z < o.Position.z;
			if (TexCoords.x != o.TexCoords.x) return TexCoords.x < o.TexCoords.x;
			return TexCoords.y < o.TexCoords.y;
		}
	};
	
	class Mesh {
		public:
			Mesh(const std::string &objFilePath);
			~Mesh();

			void Use();

		private:
			std::vector<Vertex> Vertices;
			std::vector<unsigned int> Indices;
			unsigned int VAO, VBO, EBO;
	};
}

#endif /* MESH_HPP */