#pragma once
#include "Singleton.h"

class itemDataMgr : public Singleton<itemDataMgr>
{
	friend class Singleton<itemDataMgr>;

protected:
	std::vector<ItemInfo> items;
	std::unordered_map<std::string, std::vector<ItemInfo>> shopItemMap; //key: store name , value: list of items
public: 
	void Load(const std::string& filename);
	void LoadShopItems(const std::string& filename);
	const std::vector<ItemInfo>& GetShopItemList(const std::string& shopName);
	const ItemInfo GetItem(const std::string& id);
};

	