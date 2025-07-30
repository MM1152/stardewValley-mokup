#pragma once
#include "InGameItem.h"
#include "Crops.h"

class Crops;

class Seeds : public InGameItem
{
protected:

	Crops* crops;

public:
	Seeds() = default;
	Seeds(ItemInfo info);
	~Seeds() override = default;

	bool UseItem() override;
};

