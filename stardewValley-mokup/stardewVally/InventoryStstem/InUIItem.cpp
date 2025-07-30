#include "stdafx.h"
#include "InUIItem.h"

InUIItem::InUIItem(ItemInfo type)
	:Item(type , true)
{
}

void InUIItem::Update(float dt)
{
	if (isDrag) {
		SetPosition((sf::Vector2f)InputMgr::GetMouseUIRect().getPosition());
	}
}

void InUIItem::DragItem(bool isDrag)
{
	this->isDrag = isDrag;
}

