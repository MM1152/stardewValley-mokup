#pragma once
#include "Singleton.h"

class itemDataMgr : public Singleton<itemDataMgr>
{
	friend class Singleton<itemDataMgr>;

protected:
	std::unordered_map<std::string, std::vector<ItemInfo>> shopItemMap; //key: store name , value: list of items
public: 

	void LoadJson(const std::string& filename);

	const std::vector<ItemInfo>& GetItem(const std::string& shopName);

};

