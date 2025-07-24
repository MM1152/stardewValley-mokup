#pragma once
#include "Scene.h"
#include "TileMap.h"

class TileMap;

class MapTool : public Scene
{
protected:
	bool isTile = false;
	
	sf::RectangleShape rightBackGround;

	TileMap* tilemap1 = nullptr;
	TileMap* gridTile = nullptr;
	TileMap* drawTile = nullptr;

	sf::Vector2f mousePos;
	sf::FloatRect bouns;

	sf::Vector2f texcoor[4];

	sf::RectangleShape mouseRect;


	sf::Vector2f dragStartPos;
public:
	static int drawTileIdx;
	MapTool();
	~MapTool() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void Exit() override;
	void DragToMoveScreen(float dt);
};

