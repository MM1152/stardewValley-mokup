#pragma once
#include "Scene.h"
#include "TileMap.h"

class TileMap;

class MapTool : public Scene
{
protected:
	bool isTile = false;

	TileMap* tilemap1 = nullptr;


	sf::Vector2f mousePos;
	sf::FloatRect bouns;

public:
	MapTool();
	~MapTool() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
};

