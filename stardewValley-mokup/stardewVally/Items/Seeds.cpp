#include "stdafx.h"
#include "Seeds.h"
#include "Map.h"
#include "Player.h"
#include "Crops.h"

void Seeds::UseItem()
{
	Map* map = player->GetMap();
	sf::Vector2i lookDir = player->GetLookDir();
	sf::Vector2f holePos = { player->GetPosition().x + (lookDir.x * 16.f) , player->GetPosition().y + (lookDir.y * 16.f) };

	int cellIdx = map->GetCellIndex(holePos, 0);
	int cellData = map->GetCell(cellIdx, 0).idx;

	if (cellData == 25)
	{
		copyseed = new Crops;
		copyseed->SetCropsType(Crops::CropsType::Parsnip);
		copyseed->SetPosition(player->GetPosition());
		std::cout << "µÌ³Ä?" << std::endl;
	}

}
