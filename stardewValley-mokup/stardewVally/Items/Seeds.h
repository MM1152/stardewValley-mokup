#pragma once
#include "InGameItem.h"
#include "Crops.h"

class Seeds : public InGameItem
{
protected:

	Crops* copyseed;

public:
	Seeds() = default;
	Seeds(ItemInfo info);
	~Seeds() override = default;

	void UseItem() override;
};

