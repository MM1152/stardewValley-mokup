#include "stdafx.h"
#include "DropItemFix.h"
#include "Map.h"
#include "Player.h"
#include "Inventory.h"
DropItemFix::DropItemFix(ItemInfo type , CellData* cellData)
	:InGameItem(type)
	,cellData(cellData)
{
}

void DropItemFix::Reset()
{
	InGameItem::Reset();

	SetOrigin(Origins::TL);
	SetPosition(cellData->cellPosition[0]);
}

void DropItemFix::Update(float dt)
{
	if (player && InputMgr::GetKeyDown(sf::Keyboard::C)) {
		Inventory* inv = player->GetInventory();
		inv->AddItem(*GetItemInfo());
		inv->Update(dt);
		SetActive(false);
	}
}
