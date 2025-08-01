#pragma once
#include "stdafx.h"
#include "Trigger.h"

class TileMap;
class InteractionObject;
enum GatherableType{
	None,
	Seed,
};

struct CellData {
	sf::Vector2f cellTextCoord[4];
	sf::Color cellColor[4];
	sf::Vector2f cellPosition[4];

	int idx = -1;
	GatherableType ge = GatherableType::None;
	InteractionObject* interactionObj = nullptr;
};

struct CheckCellData {
	int layer = -1;
	int idx = -1;
};

std::ostream& operator <<(std::ostream& ost, sf::Vector2f cellTextCoord[4]);


class Map
{
private:
	std::unordered_map<int, std::vector<CellData>> cell;
	std::unordered_map<int, std::string> textures;
	
	std::vector<sf::RectangleShape*> colliders;
	std::vector<Trigger*> triggers;
	std::vector<InteractionObject*> objects;
	sf::Vector2i count;

	std::vector<TileMap*> tiles;

	void Reset(int size);
	void LoadCollider(const std::string path);
	void Load(const std::string path, int layer);
	void LoadTrigger(const std::string path);

	void Init() {};
public:

	template<typename T, typename... Args>
	void Init(T first, Args... rest) {
		tiles.push_back(first);
		Init(rest...);
	}

	int GetCellIndex(const sf::Vector2f& pos, int layer);

	CellData& GetCell(int idx, int layer);
	CellData& GetCell(const sf::Vector2f& pos, int layer);

	//Search from the top line and get Cell
	CheckCellData SequentialGetCell(int idx);
	CellData GetTextureCell(int idx, int layer);

	void SetCellData(int idx, int layer, const CellData* cellData);

	void Load(const std::string path);
	
	std::vector<InteractionObject*>& CreateObjects();
	std::vector<InteractionObject*>& GetObjects() { return objects; };

	void Save(const std::string path , std::string texId, std::vector<CellData>& cellData , sf::Vector2i count);
	void Save(const std::string path, std::vector<sf::RectangleShape*>& colliderData);
	void Save(const std::string path, std::vector<Trigger*>& triggerData);

	std::string GetTextId(int layer) { return textures[layer]; };
	std::vector<CellData>& GetCellDatas(int layer);
	std::vector<sf::RectangleShape*>& GetColliders() { return colliders; };
	std::vector<Trigger*>& GetTriggers() { return triggers; };
	
	const sf::Vector2i& GetCount()  const{ return count; };

	void Release();
};

