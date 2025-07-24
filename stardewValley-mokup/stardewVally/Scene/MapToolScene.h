#pragma once
#include "Scene.h"
#include "TileMap.h"

class TileMap;
class InputText;

class MapToolScene : public Scene
{
protected:
	int xIndex;
	int yIndex;
	int index;

	bool isTile = false;
	
	sf::RectangleShape rightBackGround;

	TileMap* tilemap1 = nullptr;
	TileMap* gridTile = nullptr;
	TileMap* drawTile = nullptr;

	InputText* inputText;

	CellData cellData;
	Map map;

	sf::RectangleShape dragAreaRect;
	sf::Vector2f dragAreaStartPos;
	bool isDragArea;

	sf::Vector2f mousePos;
	sf::FloatRect bouns;
	sf::Vector2f texcoor[4];
	sf::RectangleShape mouseRect;
	sf::Vector2f dragStartPos;
public:
	static int drawTileIdx;
	MapToolScene();
	~MapToolScene() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void Exit() override;
	void DragToMoveScreen(float dt);

	bool InArea(TileMap* tile, sf::Vector2i mousePos);
};

