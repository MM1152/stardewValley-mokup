#include "stdafx.h"
#include "InGameItem.h"
#include "Player.h"
InGameItem::InGameItem(ItemInfo type)
	:Item(type , false)
{
}
void InGameItem::Update(float dt)
{
	if (player) {
		itemSp.setPosition(player->GetPosition());
	}
}

