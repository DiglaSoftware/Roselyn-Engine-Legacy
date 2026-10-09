#include "TestDrawable.hpp"
#include "Texture.hpp"
#include <glad/glad.h>

namespace RoselynEngine {
	TestDrawable::TestDrawable() {
		//float Vertices[] = {
		//	// positions        // texture coords
		//	 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // top right
		//	 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
		//	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
		//	-0.5f,  0.5f, 0.0f, 0.0f, 1.0f  // top left 
		//};

		//unsigned int Indices[] = {
		//	0, 1, 3,
		//	1, 2, 3
		//};

		float Vertices[] = {
			// Позиции                // UV
			// --- Задняя грань (-Z) ---
			-0.5f, -0.5f, -0.5f,      0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,      1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,      1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,      0.0f, 1.0f,

			// --- Передняя грань (+Z) ---
			-0.5f, -0.5f,  0.5f,      0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,      1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,      1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,      0.0f, 1.0f,

			// --- Левая грань (-X) ---
			-0.5f, -0.5f, -0.5f,      1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,      1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,      0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,      0.0f, 0.0f,

			// --- Правая грань (+X) ---
			 0.5f, -0.5f, -0.5f,      0.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,      0.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,      1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,      1.0f, 0.0f,

			 // --- Нижняя грань (-Y) ---
			 -0.5f, -0.5f, -0.5f,      0.0f, 1.0f,
			  0.5f, -0.5f, -0.5f,      1.0f, 1.0f,
			  0.5f, -0.5f,  0.5f,      1.0f, 0.0f,
			 -0.5f, -0.5f,  0.5f,      0.0f, 0.0f,

			 // --- Верхняя грань (+Y) ---
			 -0.5f,  0.5f, -0.5f,      0.0f, 1.0f,
			  0.5f,  0.5f, -0.5f,      1.0f, 1.0f,
			  0.5f,  0.5f,  0.5f,      1.0f, 0.0f,
			 -0.5f,  0.5f,  0.5f,      0.0f, 0.0f,
		};

		unsigned int Indices[] = {
			// Задняя
			0, 1, 2,  2, 3, 0,
			// Передняя
			4, 5, 6,  6, 7, 4,
			// Левая
			8, 9, 10, 10, 11, 8,
			// Правая
			12, 13, 14, 14, 15, 12,
			// Нижняя
			16, 17, 18, 18, 19, 16,
			// Верхняя
			20, 21, 22, 22, 23, 20,
		};

		glGenVertexArrays(1, &this->VAO);
		glGenBuffers(1, &this->VBO);
		glGenBuffers(1, &this->EBO);

		glBindVertexArray(this->VAO);

		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);


		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

		//Position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		//Texture coord attribute
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}

	void TestDrawable::SetTexture(RoselynEngine::Texture &texture) {
		this->Texture = new RoselynEngine::Texture(texture);
	}

	void TestDrawable::Draw() {
		if (this->Texture != nullptr)
			this->Texture->Use();

		glBindVertexArray(this->VAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}