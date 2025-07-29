#pragma once
#include "InGameItem.h"
class Hog : public InGameItem
{
public:
	Hog() = default;
	Hog(ItemInfo info);
	~Hog() override = default;

	void UseItem() override;
};

