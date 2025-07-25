#pragma once
#include "Scene.h"
#include "TileMap.h"

class TileMap;
class InputText;

enum class TriggerType {

};

class MapToolScene : public Scene
{
protected:
	int xIndex;
	int yIndex;
	int index;

	int yRange;
	int xRange;

	bool isTile = false;
	bool drawCollider = false;
	bool startDrawCollider = false;
	std::vector<sf::RectangleShape*> colliders;

	Map map;

	TileMap* tilemap1 = nullptr;
	TileMap* gridTile = nullptr;
	TileMap* drawTile = nullptr;

	InputText* inputText;

	int prevX = -1;
	int prevY = -1;
	std::vector<CellData> cellDatas;
	CellData cellData;

	bool isDragArea;

	sf::FloatRect bouns;

	sf::Vector2f dragAreaStartPos;
	sf::Vector2f mousePos;
	sf::Vector2f texcoor[4];
	sf::Vector2f dragStartPos;
	sf::Vector2f drawColliderStartPos;

	sf::RectangleShape mouseRect;
	sf::RectangleShape rightBackGround;
	sf::RectangleShape dragAreaRect;

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

