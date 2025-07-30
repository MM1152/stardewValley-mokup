#include "stdafx.h"
#include "Crops.h"
#include "TimeMoneyUi.h"
#include "SceneTest.h"
#include "DropItem.h"
#include "Inventory.h"
#include "Player.h"

Crops::Crops(const std::string& name)
	: Gatherable(name)
{
}

void Crops::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;


	SetCropsType(ctype);
	SetScale({ 1.f, 1.f });
}

void Crops::Reset()
{
	GtSp.setTexture(TEXTURE_MGR.Get(cropsId));
}

void Crops::Update(float dt)
{
	DropItems();
}

void Crops::DropItems()
{
	Map* map = player->GetMap();

	sf::Vector2i lookDir = player->GetLookDir();
	sf::Vector2f holePos = { player->GetPosition().x + (lookDir.x * 16.f) , player->GetPosition().y + (lookDir.y * 16.f) };
	int cellIdx = map->GetCellIndex(holePos, 0);
	CellData& cellData = map->GetCell(cellIdx, 0);

	SceneTest* scene = (SceneTest*)SCENE_MGR.GetCurrentScene();

	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left) && cellData.cellPosition[0] == GetCurrentCropsPosition())
	{
		if (growup_interaction)
		{
			dropitem = new DropItem("", "graphics/garlic_seeds.png");
			dropitem->Init();
			dropitem->SetPosition(GetCurrentCropsPosition());
			dropitem->SetCurrentPosition(GetCurrentCropsPosition());
			dropitem->Reset();
			scene->AddDropItem(dropitem);
			scene->RemoveCrops(scene->GetRemoveCrops(scene->GetCropsList()));
		}
	}
}

void Crops::GrowUp() {
	curGrow++;
	sf::IntRect Grow(16 * curGrow, 0, 16, 16);
	GtSp.setTextureRect(Grow);
	if (curGrow > 4 && cropsId == "graphics/parsnip.png")
	{
		curGrow = 5;
		sf::IntRect Grow(16 * curGrow, 0, 16, 16);
		GtSp.setTextureRect(Grow);
		growup_interaction = true;
	}
	else if (curGrow > 4 && cropsId == "graphics/garlic.png")
	{
		curGrow = 5;
		sf::IntRect Grow(16 * curGrow, 0, 16, 16);
		GtSp.setTextureRect(Grow);
		growup_interaction = true;
	}
	else if (curGrow > 5 && cropsId == "graphics/caluliflower.png")
	{
		curGrow = 6;
		sf::IntRect Grow(16 * curGrow, 0, 16, 16);
		GtSp.setTextureRect(Grow);
		growup_interaction = true;
	}
	else if (curGrow > 5 && cropsId == "graphics/potato.png")
	{
		curGrow = 6;
		sf::IntRect Grow(16 * curGrow, 0, 16, 16);
		GtSp.setTextureRect(Grow);
		growup_interaction = true;
	}
}

void Crops::SetCropsType(CropsType c)
{
	ctype = c;
	sf::IntRect seed(0, 0, 16, 16);
	switch (ctype)
	{
	case CropsType::Parsnip:
		cropsId = "graphics/parsnip.png";
		GtSp.setTextureRect(seed);
		break;
	case CropsType::Cauliflower:
		cropsId = "graphics/caluliflower.png";
		GtSp.setTextureRect(seed);
		break;
	case CropsType::Potato:
		cropsId = "graphics/potato.png";
		GtSp.setTextureRect(seed);
		break;
	case CropsType::Garlic:
		cropsId = "graphics/garlic.png";
		GtSp.setTextureRect(seed);
		break;
	}
}



void Crops::Setidx(int index)
{
	idx = index;
}

int Crops::Getidx()
{
	return idx;
}
Crops::CropsType Crops::GetCropsType()
{
	return ctype;
}
void Crops::SetTimeMoneyUi(TimeMoneyUi* time)
{
	tm = time;
}

TimeMoneyUi* Crops::GetTimeMoneyUi()
{
	return tm;
}
