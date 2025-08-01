#pragma once
#include "InteractionObject.h"
class Stone : public InteractionObject
{
public:
	Stone(const std::string& texId, CellData* cellData, const std::string& name = "");
	~Stone() override = default;

	void Reset() override;
};

	