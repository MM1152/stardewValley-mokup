#pragma once
#include "stdafx.h"

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
	std::string texId;
	std::unordered_map<int, std::vector<CellData>> cell;
	std::vector<sf::RectangleShape*> colliders;
	void Reset(int size);

public:
	int GetCellIndex(int idx , int layer);

	std::vector<sf::RectangleShape*>& Load(const std::string path);
	std::vector<CellData>& Load(const std::string path , int layer);
	void Save(const std::string path , std::string texId, std::vector<CellData>& cellData , sf::Vector2i count);
	void Save(const std::string path, std::vector<sf::RectangleShape*>& colliderData);
	std::string GetTextId() { return texId; };

	void Release();
	std::vector<sf::RectangleShape*>& GetColliders() { return colliders; };
};

