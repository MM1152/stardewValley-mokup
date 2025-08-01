#include "stdafx.h"
#include "Grass.h"
#include "Map.h"
#include "DropItemFix.h"
Grass::Grass(const std::string& texId, CellData* cellData, const std::string& name)
	:InteractionObject(texId, cellData , name)
{
}

void Grass::Reset()
{
	InteractionObject::Reset();
	rect.setSize({ 16,16 });
	rect.setPosition(cellData->cellPosition[0]);
}

void Grass::Interaction()
{
	DropItemFix* item = new DropItemFix(itemDataMgr::Instance().GetItem("grass") , cellData);
	SCENE_MGR.GetCurrentScene()->SetDropItem(item);

	SetActive(false);
	InteractionObject::Interaction();
}
