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

    items.clear();
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
        info.quantity = item["quantity"];

        if (item.contains("UiTextureRect")) {
            info.uiTextCoord.left = item["UiTextureRect"][0];
            info.uiTextCoord.top = item["UiTextureRect"][1];
            info.uiTextCoord.width = item["UiTextureRect"][2];
            info.uiTextCoord.height = item["UiTextureRect"][3];
        }
        if (item.contains("TextureRect")) {
            info.textureCoord.left = item["TextureRect"][0];
            info.textureCoord.top = item["TextureRect"][1];
            info.textureCoord.width = item["TextureRect"][2];
            info.textureCoord.height = item["TextureRect"][3];
        }
        info.itemType = ItemType::None;
        items.push_back(info);
        std::cout << info.itemId << std::endl;
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
    shopItemMap.clear();

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

void itemDataMgr::LoadDropItems(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "JSON failed " << filename << "\n";
        return;
    }

    items.clear();
    nlohmann::json data;
    file >> data;

    for (const auto& item : data["items"]) {
        DropItemInfo info;
        info.itemId = item["id"];
        info.itemName = item["name"];
        info.itemTextureId = item["TextureId"];
        info.itemDes = item["description"];
        info.cell_price = item["cell_price"];
        info.stock = item["stock"];

        if (item.contains("UiTextureRect")) {
            info.uiTextCoord.left = item["UiTextureRect"][0];
            info.uiTextCoord.top = item["UiTextureRect"][1];
            info.uiTextCoord.width = item["UiTextureRect"][2];
            info.uiTextCoord.height = item["UiTextureRect"][3];
        }
        if (item.contains("TextureRect")) {
            info.textureCoord.left = item["TextureRect"][0];
            info.textureCoord.top = item["TextureRect"][1];
            info.textureCoord.width = item["TextureRect"][2];
            info.textureCoord.height = item["TextureRect"][3];
        }
        info.itemType = DropItemType::None;
        dropitems.push_back(info);
        std::cout << info.itemId << std::endl;
    }
}


const std::vector<ItemInfo>& itemDataMgr::GetShopItemList(const std::string& shopName)
{
	return shopItemMap[shopName];
}

const ItemInfo itemDataMgr::GetItem(const std::string& id)
{
    ItemInfo iteminfo;
    
    for (auto item : items) {
        if (item.itemId == id) {
            return item;
        }
    }
    return iteminfo;
}

const DropItemInfo itemDataMgr::GetDropItem(const std::string& id)
{
    DropItemInfo dropiteminfo;

    for (auto dropitem : dropitems)
    {
        if (dropitem.itemId == id) {
            return dropitem;
        }
    }

    return dropiteminfo;
}

