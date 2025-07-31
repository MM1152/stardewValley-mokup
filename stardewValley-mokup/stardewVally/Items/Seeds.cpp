#include "stdafx.h"
#include "Seeds.h"
#include "Map.h"
#include "Player.h"
#include "Crops.h"
#include "SceneFarm.h"

Seeds::Seeds(ItemInfo info)
	:InGameItem(info)
{
}

bool Seeds::UseItem()
{
	if (parentItem->GetQuantity() <= 0) return false;

	Map* map = player->GetMap();

	sf::Vector2i lookDir = player->GetLookDir();
	sf::Vector2f holePos = { player->GetPosition().x + (lookDir.x * 16.f) , player->GetPosition().y + (lookDir.y * 16.f) };

	int cellIdx = map->GetCellIndex(holePos, 0);
	CellData& cellData = map->GetCell(cellIdx, 0);
	if (cellData.idx == 308 && GetItemInfo()->itemId == "parsnip_seeds")
	{
		if (cellData.ge == GatherableType::None) {
			SceneFarm* scene = (SceneFarm*)SCENE_MGR.GetCurrentScene();
			cellData.ge = GatherableType::Seed;
			crops = new Crops;
			crops->Init();
			crops->Setidx(cellIdx);
			crops->SetPosition(cellData.cellPosition[0]);
			crops->SetCurrentCropsPosition(cellData.cellPosition[0]);
			crops->SetCropsType(Crops::CropsType::Parsnip);
			crops->Reset();
			scene->AddCrops(crops);
			parentItem->PlusQuantity(-1);

			return InGameItem::UseItem();
		}
	}
	if (cellData.idx == 308 && GetItemInfo()->itemId == "cauliflower_seeds")
	{
		if (cellData.ge == GatherableType::None) {
			SceneFarm* scene = (SceneFarm*)SCENE_MGR.GetCurrentScene();
			cellData.ge = GatherableType::Seed;
			crops = new Crops;
			crops->Init();
			crops->Setidx(cellIdx);
			crops->SetPosition(cellData.cellPosition[0]);
			crops->SetCurrentCropsPosition(cellData.cellPosition[0]);
			crops->SetCropsType(Crops::CropsType::Cauliflower);
			crops->Reset();
			scene->AddCrops(crops);
			parentItem->PlusQuantity(-1);

			return InGameItem::UseItem();
		}
	}
	if (cellData.idx == 308 && GetItemInfo()->itemId == "potato_seeds")
	{
		if (cellData.ge == GatherableType::None) {
			SceneFarm* scene = (SceneFarm*)SCENE_MGR.GetCurrentScene();
			cellData.ge = GatherableType::Seed;
			crops = new Crops;
			crops->Init();
			crops->Setidx(cellIdx);
			crops->SetPosition(cellData.cellPosition[0]);
			crops->SetCurrentCropsPosition(cellData.cellPosition[0]);
			crops->SetCropsType(Crops::CropsType::Potato);
			crops->Reset();
			scene->AddCrops(crops);
			parentItem->PlusQuantity(-1);

			return InGameItem::UseItem();
		}
	}
	if (cellData.idx == 308 && GetItemInfo()->itemId == "garlic_seeds")
	{
		if (cellData.ge == GatherableType::None) {
			SceneFarm* scene = (SceneFarm*)SCENE_MGR.GetCurrentScene();
			cellData.ge = GatherableType::Seed;
			crops = new Crops;
			crops->Init();
			crops->Setidx(cellIdx);
			crops->SetPosition(cellData.cellPosition[0]);
			crops->SetCurrentCropsPosition(cellData.cellPosition[0]);
			crops->SetCropsType(Crops::CropsType::Garlic);
			crops->Reset();
			scene->AddCrops(crops);
			parentItem->PlusQuantity(-1);

			return InGameItem::UseItem();
		}
	}
	return false;
}
