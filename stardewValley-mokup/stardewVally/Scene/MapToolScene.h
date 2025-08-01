#pragma once
#include "Scene.h"
#include "TileMap.h"

class TileMap;
class InputText;
class Trigger;
class Button;


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
	bool startDraw = false;
	bool drawTrigger = false;
	bool isShowTriggerBox = false;

	//gotitle
	bool gotitleview = false;
	sf::Sprite gotitleyes_or_no;

	std::vector<sf::RectangleShape*> colliders;
	std::vector<Trigger*> triggers;
	std::vector<Button*> triggerTypeButton;

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
	sf::Vector2f drawStartPos;

	sf::RectangleShape mouseRect;
	sf::RectangleShape rightBackGround;
	sf::RectangleShape dragAreaRect;

	Button* objects;
	Button* triggerButton;
	Button* deleteBNT;
	Button* buildingBNT;
	Button* tileBNT;
	Button* saveBNT;
	Button* loadBNT;
	Button* colliderBNT;

	Button* gotitleBNT;
	Button* gtyesBNT;
	Button* gtnoBNT;

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
	void SelectTile();
	void DrawTile();
	void DrawColliderBox();
	void DrawTriggerBox();

	void Setgotitleview(bool view) { gotitleview = view; }
};

