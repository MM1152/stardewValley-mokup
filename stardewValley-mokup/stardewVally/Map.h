#pragma once
#include "stdafx.h"
#include "Trigger.h"
struct CellData {
	sf::Vector2f cellTextCoord[4];
	sf::Color cellColor[4];
	sf::Vector2f cellPosition[4];

	int idx = -1;
};


//������ �ʸ��� Ư�� �ε����� Ư�� ������ �� �־����
//��� ����?
//MAP���� �ε��Ҷ� ��ȯ���Ѽ� ���� �Ѱ��ش�?
//�ٵ� �̰� ������ Ÿ�ϻ����� 16*16 �̴ϱ� ��ȯ�� Load���� �������ش�?
//�׷� TILEMAP�� set������ va�� �޾�?
//�ƴ��� CellData�� ä��� �Ǵ°Ű�
//��ġ
class Map
{
private:
	std::unordered_map<int, std::vector<CellData>> cell;
	std::unordered_map<int, std::string> textures;

	std::vector<sf::RectangleShape*> colliders;
	std::vector<Trigger*> triggers;
	void Reset(int size);

	void LoadCollider(const std::string path);
	void Load(const std::string path, int layer);
	void LoadTrigger(const std::string path);
public:
	int GetCellIndex(int idx , int layer);

	void Load(const std::string path);
	
	void Save(const std::string path , std::string texId, std::vector<CellData>& cellData , sf::Vector2i count);
	void Save(const std::string path, std::vector<sf::RectangleShape*>& colliderData);
	void Save(const std::string path, std::vector<Trigger*>& triggerData);

	std::string GetTextId(int layer) { return textures[layer]; };
	std::vector<CellData>& GetCellData(int layer);
	std::vector<sf::RectangleShape*>& GetColliders() { return colliders; };
	std::vector<Trigger*>& GetTriggers() { return triggers; };

	void Release();
};

