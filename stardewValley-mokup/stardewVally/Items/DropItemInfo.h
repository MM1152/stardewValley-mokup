#pragma once

enum class DropItemType {
	Crops,
	Stone,
	Grass,
	None,
};

struct DropItemInfo {
	std::string itemId;
	std::string itemName;
	std::string itemTextureId;
	std::string itemDes;

	sf::FloatRect uiTextCoord = { -1,-1,-1,-1 };
	sf::FloatRect textureCoord = { -1,-1,-1,-1 };

	int cell_price = 0;
	int stock = 0;

	DropItemType itemType = DropItemType::None;
};