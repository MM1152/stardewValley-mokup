#pragma once
#include "Scene.h"
#include "TileMap.h"

class TileMap;

class MapTool : public Scene
{
protected:

	TileMap* tilemap1 = nullptr;

public:
	MapTool();
	~MapTool() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
};

