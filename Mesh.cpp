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
            std::cout << "Failed to load OBJ: " << warn << err << std::endl;
        }

        // Используем хэш-таблицу для дедупликации вершин (оптимизация памяти и производительности)
        std::map<Vertex, unsigned int> uniqueVertices{};

        // Перебираем все шейпы (обычно один для OBJ)
        for (const auto& shape : shapes) {
            for (const auto& index : shape.mesh.indices) {
                Vertex vertex{};

                // 1. Позиция
                vertex.Position = {
                    attrib.vertices[3 * index.vertex_index + 0],
                    attrib.vertices[3 * index.vertex_index + 1],
                    attrib.vertices[3 * index.vertex_index + 2]
                };

                // 2. Текстурные координаты (если есть)
                if (index.texcoord_index >= 0) {
                    vertex.TexCoords = {
                        attrib.texcoords[2 * index.texcoord_index + 0],
                        attrib.texcoords[2 * index.texcoord_index + 1]
                    };
                }
                else {
                    vertex.TexCoords = glm::vec2(0.0f);
                }

                // Дедупликация: если вершины с такими атрибутами еще не было — добавляем
                if (uniqueVertices.count(vertex) == 0) {
                    uniqueVertices[vertex] = static_cast<unsigned int>(Vertices.size());
                    Vertices.push_back(vertex);
                }

                Indices.push_back(uniqueVertices[vertex]);
            }
        }

        std::cout << "Loaded " << Vertices.size() << " vertices, "
            << Indices.size() << " indices." << std::endl;

        glGenVertexArrays(1, &this->VAO);
        glGenBuffers(1, &this->VBO);
        glGenBuffers(1, &this->EBO);

        glBindVertexArray(this->VAO);

        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferData(GL_ARRAY_BUFFER, this->Vertices.size() * sizeof(Vertex), this->Vertices.data(), GL_STATIC_DRAW);

        // Загружаем индексы
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->Indices.size() * sizeof(unsigned int), this->Indices.data(), GL_STATIC_DRAW);

        // Атрибут 0: Position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));

        // Атрибут 2: TexCoords
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

        glBindVertexArray(0);
	}

    Mesh::~Mesh() {
    
    }

    void Mesh::Use() {
        glBindVertexArray(this->VAO);
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(Indices.size()), GL_UNSIGNED_INT, 0);
    }
}