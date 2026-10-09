#ifndef TGA_LOADER_HPP
#define TGA_LOADER_HPP

#include <string>

namespace RoselynEngine {
	class TGALoader {
		public:
			static unsigned char* LoadTGA(const std::string &FilePath, int &Width, int &Height, int &NrChannels);
	};
}

#endif /* TGA_LOADER_HPP */