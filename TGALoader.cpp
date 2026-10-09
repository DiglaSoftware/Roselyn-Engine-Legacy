#include "TGALoader.hpp"
#include <fstream>
#include <iostream>
#include <string>

namespace RoselynEngine {
	unsigned char* TGALoader::LoadTGA(const std::string &FilePath, int &Width, int &Height, int &NrChannels) {
		std::ifstream ImageFile(FilePath, std::ios::binary);
		if (!ImageFile) {
			return nullptr;
		}

		unsigned char TGAHeader[18];
		ImageFile.read(reinterpret_cast<char*>(TGAHeader), sizeof(TGAHeader));
		if (TGAHeader[2] != 2) {
			std::cout << "ROSELYN::LOADERS::TGA-LOADER::ERROR | Unsupported TGA format" << std::endl;
			return nullptr;
		}

		Width = TGAHeader[12] | (TGAHeader[13] << 8);
		Height = TGAHeader[14] | (TGAHeader[15] << 8);
		NrChannels = TGAHeader[16] / 8;

		if (NrChannels != 3 && NrChannels != 4) {
			std::cout << "ROSELYN::LOADERS::TGA-LOADER::ERROR | Unsupported TGA channel count (24-bit or 32-bit only)" << std::endl;
			return nullptr;
		}

		if (Width <= 0 || Height <= 0 || NrChannels <= 0) {
			std::cout << "ROSELYN::LOADERS::TGA-LOADER::ERROR | Invalid TGA dimensions or channels" << std::endl;
			return nullptr;
		}

		int ImageSize = Width * Height * NrChannels;
		unsigned char* ImageData = new unsigned char[ImageSize];
		
		bool IsTopLeft = (TGAHeader[17] & 0x20) == 0;

		if (IsTopLeft) {
			ImageFile.read(reinterpret_cast<char*>(ImageData), ImageSize);
		}
		else {
			unsigned char* TempData = new unsigned char[ImageSize];
			ImageFile.read(reinterpret_cast<char*>(TempData), ImageSize);
			
			int RowSize = Width * NrChannels;
			for (int y = 0; y < Height; ++y) {
				std::copy(TempData + (Height - 1 - y) * RowSize, TempData + (Height - y) * RowSize, ImageData + y * RowSize);
			}

			delete[] TempData;
		}

		for (int i = 0; i < ImageSize; i += NrChannels) {
			std::swap(ImageData[i], ImageData[i + 2]);
		}

		return ImageData;
	}
}