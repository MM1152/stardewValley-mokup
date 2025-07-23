#pragma once
#include "stdafx.h"

enum class ItemType{
	Seed,
	EquipMent,
	None,
};

struct ItemInfo {
	std::string itemName;
	std::string itemTextureId;
	
	ItemType itemType;
};

