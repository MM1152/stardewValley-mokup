#include "stdafx.h"
#include "Grass.h"

Grass::Grass(const std::string& texId, CellData* cellData, const std::string& name)
	:InteractionObject(texId, cellData , name)
{
}

void Grass::Reset()
{
	InteractionObject::Reset();
}
