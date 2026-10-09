#include "Texture.hpp"
#include <glad/glad.h>
#include <iostream>
#include "TGALoader.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace RoselynEngine {
	Texture::Texture() {
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glGenTextures(1, &this->GLTexture);
		glBindTexture(GL_TEXTURE_2D, this->GLTexture);

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		unsigned char test[8 * 8 * 3];

		for (int y = 0; y < 8; y++) {
			for (int x = 0; x < 8; x++) {
				if (x % 2 == 0 || y % 2 == 0) {
					test[(y * 8 + x) * 3 + 0] = 255;
					test[(y * 8 + x) * 3 + 1] = 0;
					test[(y * 8 + x) * 3 + 2] = 255;
				}
				else {
					test[(y * 8 + x) * 3 + 0] = 0;
					test[(y * 8 + x) * 3 + 1] = 0;
					test[(y * 8 + x) * 3 + 2] = 0;
				}
			}
		}

		unsigned char* data = test;
		this->Width = 8;
		this->Height = 8;
		this->NrChannels = 3;

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->Width, this->Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
		return;
	}

	//Texture::Texture(const std::string& filePath) {
	//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	//	glGenTextures(1, &this->GLTexture);
	//	glBindTexture(GL_TEXTURE_2D, this->GLTexture);

	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//	unsigned char* data = TGALoader::LoadTGA(filePath, this->Width, this->Height, this->NrChannels);
	//	std::cout << "ROSELYN::RENDY::TEXTURE::INFO | " << this->Width << " | " << this->Height << " | " << this->NrChannels << std::endl;

	//	if (data) {
	//		GLenum ColorFormat = GL_RGB;
	//		switch (this->NrChannels) {
	//		case 1:
	//			ColorFormat = GL_RED;
	//			break;
	//		case 3:
	//			ColorFormat = GL_RGB;
	//			break;
	//		case 4:
	//			ColorFormat = GL_RGBA;
	//			break;
	//		}

	//		glEnable(GL_BLEND);
	//		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//		glTexImage2D(GL_TEXTURE_2D, 0, ColorFormat, this->Width, this->Height, 0, ColorFormat, GL_UNSIGNED_BYTE, data);
	//		glGenerateMipmap(GL_TEXTURE_2D);
	//	}
	//	else {
	//		std::cout << "ROSELYN::RENDY::TEXTURES | Failed to load texture" << std::endl;
	//	}
	//	delete[] data;

	//	glEnable(GL_BLEND);
	//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->Width, this->Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	//	glGenerateMipmap(GL_TEXTURE_2D);

	//	glBindTexture(GL_TEXTURE_2D, 0);
	//}

	//Texture::Texture(const Texture& other) {
	//	this->Width = other.Width;
	//	this->Height = other.Height;
	//	this->NrChannels = other.NrChannels;
	//	this->GLTexture = other.GLTexture;
	//}

	void Texture::LoadFromFile(const std::string &filePath) {
		glBindTexture(GL_TEXTURE_2D, this->GLTexture);
		//unsigned char* data = TGALoader::LoadTGA(filePath, this->Width, this->Height, this->NrChannels);
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(filePath.c_str(), &this->Width, &this->Height, &this->NrChannels, 0);
		std::cout << "ROSELYN::RENDY::TEXTURE::INFO | " << this->Width << " | " << this->Height << " | " << this->NrChannels << std::endl;

		if (data) {
			GLenum ColorFormat = GL_RGB;
			switch (this->NrChannels) {
			case 1:
				ColorFormat = GL_RED;
				break;
			case 3:
				ColorFormat = GL_RGB;
				break;
			case 4:
				ColorFormat = GL_RGBA;
				break;
			}

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glTexImage2D(GL_TEXTURE_2D, 0, ColorFormat, this->Width, this->Height, 0, ColorFormat, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			std::cout << "ROSELYN::RENDY::TEXTURES | Failed to load texture" << std::endl;
		}
		//delete[] data;
		stbi_image_free(data);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::Use() {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, this->GLTexture);
	}
}