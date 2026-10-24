#include "LevelManager.hpp"
#include "Level.hpp"

namespace RoselynEngine {
	Level* LevelManager::CurrentLevel = nullptr;

	void LevelManager::LoadLevel(Level* level) {
		LevelManager::CurrentLevel = level;
	}

	const Level* LevelManager::GetCurrentLevel() {
		return LevelManager::CurrentLevel;
	}
}