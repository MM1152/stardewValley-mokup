#include "stdafx.h"
#include "Hog.h"
#include "Map.h"
#include "Player.h"
Hog::Hog(ItemInfo info)
	:InGameItem(info)
{
}

void Hog::UseItem()
{
	Map* map = player->GetMap();
	sf::Vector2i lookDir = player->GetLookDir();
	sf::Vector2f holePos = { player->GetPosition().x + (lookDir.x * 16.f) , player->GetPosition().y + (lookDir.y * 16.f) };

	int cellIdx = map->GetCellIndex(holePos, 0);
	int cellData = map->GetCell(cellIdx, 0).idx;
	
	if (cellData == 25) {
		CellData changeCellData = map->GetTextureCell(308, 0);
		map->SetCellData(cellIdx , 0 , &changeCellData);
		
	}
}
