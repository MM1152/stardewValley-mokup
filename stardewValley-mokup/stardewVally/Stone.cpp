#include "stdafx.h"
#include "Stone.h"

Stone::Stone(const std::string& texId, CellData* cellData, const std::string& name)	
	:InteractionObject(texId , cellData , name)
{
}

void Stone::Reset()
{
	InteractionObject::Reset();

	this->rect.setSize({ 16 , 16 });
	this->rect.setPosition(objectSp.getPosition());
}
