#pragma once
#include "stdafx.h"

enum class ItemType{
	Seed,
	EquipMent,
	None,
};

struct ItemInfo {
	std::string itemId;
	std::string itemName;
	std::string itemTextureId;
	std::string itemDes;
	int price = 0;
	int stock = 0;
	
	ItemType itemType;
};

