#include "Engine.hpp"
#include "AssetWarehouse.hpp"
#include "Level.hpp"
#include "LevelManager.hpp"
#include "StaticMesh.hpp"
#include "Camera.hpp"
#include "TestPlayer.hpp"

using namespace RoselynEngine;

int main() {
	Engine::Init();

	AssetWarehouse::Init();
	AssetWarehouse::LoadTexture("Tiles.png", "TEX_tiles");
	AssetWarehouse::LoadMesh("abc.obj", "MESH_map");

	Level testLevel;
	LevelManager::LoadLevel(&testLevel);

	RoselynEngine::Camera asd;
	asd.Make3D(90.0f, Engine::GetWindow()->GetAspect(), 0.1f, 1000000.0f);

	StaticMesh testStaticMesh("MESH_map", "TEX_tiles");
	testStaticMesh.SetShader(ShaderType::Lit);

	RoselynGame::TestPlayer player;

	testLevel.Objects.push_back(&player);
	testLevel.Objects.push_back(&testStaticMesh);
	testLevel.LevelCamera = &asd;

	Engine::Run();

	Engine::Shutdown();
}