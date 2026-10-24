#ifndef LEVEL_MANAGER_HPP
#define LEVEL_MANAGER_HPP

#include "Level.hpp"

namespace RoselynEngine {
	class LevelManager {
		public:
			static void LoadLevel(Level* level);
			static const Level* GetCurrentLevel();

		private:
			static Level* CurrentLevel;
	};
}

#endif /* LEVEL_MANAGER_HPP */