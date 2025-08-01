#pragma once
#include "InteractionObject.h"
class Grass : public InteractionObject
{
public:
	Grass(const std::string& texId, CellData* cellData, const std::string& name = "");
	~Grass() override = default;

	void Reset() override;

};

