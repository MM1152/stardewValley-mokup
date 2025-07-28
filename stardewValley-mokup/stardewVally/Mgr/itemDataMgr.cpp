#include "stdafx.h"
#include "itemDataMgr.h"
#include <fstream>

void itemDataMgr::LoadJson(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "JSON failed " << filename << "\n";
        return;
    }

    nlohmann::json data;
    file >> data;


    if (!data.contains("storeName") || !data.contains("items"))
    {
        std::cerr << " JSON¿¡ 'storeName' ¶Ç´Â 'items' X\n";
        return;
    }

    std::string shopName = data["storeName"];
    std::vector<ItemInfo>& items = shopItemMap[shopName];
    items.clear();

    for (const auto& item : data["items"])
    {
        ItemInfo info;
        info.itemId = item["id"];
        info.itemName = item["name"];
        info.itemTextureId = item["TextureId"];
        info.itemDes = item["description"];
        info.price = item["price"];
        info.stock = item["stock"];

        std::string typeStr = item.value("type", "None");
        if (typeStr == "Seed") info.itemType = ItemType::Seed;
        else if (typeStr == "Equip") info.itemType = ItemType::EquipMent;
        else info.itemType = ItemType::None;

        items.push_back(info);
    }
}


const std::vector<ItemInfo>& itemDataMgr::GetItem(const std::string& shopName)
{
	return shopItemMap[shopName];
}

