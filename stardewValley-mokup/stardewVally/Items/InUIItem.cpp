#include "stdafx.h"
#include "InUIItem.h"

InUIItem::InUIItem(ItemInfo type)
	:Item(type , true)
{
}

InUIItem::InUIItem(DropItem* drop)
	:Item(drop, true)
{
}

void InUIItem::Update(float dt)
{
	if (isDrag) {
		SetPosition((sf::Vector2f)InputMgr::GetMouseUIRect().getPosition());
	}
}

void InUIItem::DragItem()
{
	isDrag = true;
}
