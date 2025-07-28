#include "stdafx.h"
#include "itemDataMgr.h"
#include <fstream>

void itemDataMgr::Load(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "JSON failed " << filename << "\n";
        return;
    }

    nlohmann::json data;
    file >> data;

    for (const auto& item : data["items"]) {
        ItemInfo info;
        info.itemId = item["id"];
        info.itemName = item["name"];
        info.itemTextureId = item["TextureId"];
        info.itemDes = item["description"];
        info.price = item["price"];
        info.stock = item["stock"];

        info.itemType = ItemType::None;

        items.push_back(info);
    }
}

void itemDataMgr::LoadShopItems(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "JSON failed " << filename << "\n";
        return;
    }

    nlohmann::json data;
    file >> data;

    auto shopInfo = data["shopInfo"];
    for (auto it = shopInfo.begin(); it != shopInfo.end(); ++it) {
        std::string shopName = it.key();                  
        const auto& itemList = it.value();                

        shopItemMap.insert({ shopName , std::vector<ItemInfo>() });
        for (const auto& itemId : itemList) {
            for (auto item : items) {
                if (itemId == item.itemId) {
                    shopItemMap[shopName].push_back(item);
                    break;
                }
            }
            
        }
    }
    
}


const std::vector<ItemInfo>& itemDataMgr::GetItem(const std::string& shopName)
{
	return shopItemMap[shopName];
}

