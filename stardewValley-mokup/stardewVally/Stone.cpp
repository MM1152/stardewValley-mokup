#include "stdafx.h"
#include "Stone.h"
#include "DropItemFix.h"

Stone::Stone(const std::string& texId, CellData* cellData, const std::string& name)	
	:InteractionObject(texId , cellData , name)
{
}

void Stone::Reset()
{
	InteractionObject::Reset();
	if(!isBroken) {
		this->rect.setSize({ 16 , 16 });
		this->rect.setPosition(objectSp.getPosition());
	}

}

void Stone::Interaction()
{
	DropItemFix* item = new DropItemFix(itemDataMgr::Instance().GetItem("stone") , cellData);
	
	SCENE_MGR.GetCurrentScene()->SetDropItem(item);
	SetActive(false);
	InteractionObject::Interaction();
}
