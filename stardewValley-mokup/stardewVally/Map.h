#pragma once
#include "stdafx.h"
#include "Trigger.h"

struct CellData {
	sf::Vector2f cellTextCoord[4];
	sf::Color cellColor[4];
	sf::Vector2f cellPosition[4];

	int idx = -1;

};
std::ostream& operator <<(std::ostream& ost, sf::Vector2f cellTextCoord[4]);


//각각의 맵마다 특정 인덱스에 특정 값들이 들어가 있어야함
//어떻게 하지?
//MAP에서 로드할때 변환시켜서 값을 넘겨준다?
//근데 이거 어차피 타일사이즈 16*16 이니까 변환은 Load에서 진행해준다?
//그럼 TILEMAP의 set에서는 va를 받아?
//아니지 CellData를 채우면 되는거고
//그치
class TileMap;
class Map
{
private:
	std::unordered_map<int, std::vector<CellData>> cell;
	std::unordered_map<int, std::string> textures;
	
	std::vector<sf::RectangleShape*> colliders;
	std::vector<Trigger*> triggers;
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

	//실제 맵에 적용되어있는 셀 데이터 가져오는 부분
	CellData& GetCell(int idx, int layer);
	CellData& GetCell(const sf::Vector2f& pos, int layer);

	//텍스처에서 특정부분 가져오기
	CellData GetTextureCell(int idx, int layer);

	void SetCellData(int idx, int layer, const CellData* cellData);

	void Load(const std::string path);
	
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

