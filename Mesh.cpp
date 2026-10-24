#define TINYOBJLOADER_DISABLE_FAST_FLOAT
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "Mesh.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <glad/glad.h>

namespace RoselynEngine {
	Mesh::Mesh(const std::string &objFilePath) {
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string warn, err;

		if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, objFilePath.c_str())) {
			std::cout << "ROSELYN::MESH | Failed to load obj: " << warn << err << std::endl;
		}

		std::map<Vertex, unsigned int> uniqueVertices{};

		// all shapes (models)
		for (const auto& shape : shapes) {
			for (const auto& index : shape.mesh.indices) {
				Vertex vertex = {};

				// pos
				vertex.Position = {
					attrib.vertices[3 * index.vertex_index + 0],
					attrib.vertices[3 * index.vertex_index + 1],
					attrib.vertices[3 * index.vertex_index + 2]
				};

				// UV
				if (index.texcoord_index >= 0) {
					vertex.TexCoords = {
						attrib.texcoords[2 * index.texcoord_index + 0],
						attrib.texcoords[2 * index.texcoord_index + 1]
					};
				}
				else {
					vertex.TexCoords = glm::vec2(0.0f);
				}

				// Normal
				if (index.normal_index >= 0) {
					vertex.Normal = {
						attrib.normals[3 * index.normal_index + 0],
						attrib.normals[3 * index.normal_index + 1],
						attrib.normals[3 * index.normal_index + 2]
					};
				}
				else {
					vertex.Normal = glm::vec3(0.0f);
				}

				if (uniqueVertices.count(vertex) == 0) {
					uniqueVertices[vertex] = static_cast<unsigned int>(Vertices.size());
					Vertices.push_back(vertex);
				}

				Indices.push_back(uniqueVertices[vertex]);
			}
		}

		std::cout << "ROSELYN::MESH | Mesh loaded " << Vertices.size() << " vertices, "
			<< Indices.size() << " indices." << std::endl;

		glGenVertexArrays(1, &this->VAO);
		glGenBuffers(1, &this->VBO);
		glGenBuffers(1, &this->EBO);

		glBindVertexArray(this->VAO);

		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, this->Vertices.size() * sizeof(Vertex), this->Vertices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->Indices.size() * sizeof(unsigned int), this->Indices.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

		glBindVertexArray(0);
	}

	Mesh::~Mesh() {
		glDeleteVertexArrays(1, &this->VAO);
		glDeleteBuffers(1, &this->VBO);
		glDeleteBuffers(1, &this->EBO);
	}

	void Mesh::Draw() {
		glBindVertexArray(this->VAO);
		glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(Indices.size()), GL_UNSIGNED_INT, 0);
	}
}