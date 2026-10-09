#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

namespace RoselynEngine {
	class Texture {
		public:
			Texture();
			//Texture(const std::string &filePath);
			//Texture(const Texture &other);
			void LoadFromFile(const std::string &filePath);
			void Use();
		private:
			int Width = 0, Height = 0, NrChannels = 0;
			unsigned int GLTexture = 0;
	};
}

#endif /* TEXTURE_HPP */