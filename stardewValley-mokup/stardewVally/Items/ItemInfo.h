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

	sf::FloatRect uiTextCoord = { -1,-1,-1,-1 };
	sf::FloatRect textureCoord = {-1,-1,-1,-1};

	int price = 0;
	int stock = 0;
	int quantity = 1;

	ItemType itemType = ItemType::None;

	std::vector<int> usableTiles; 
	int usableLayer = -1;
};

